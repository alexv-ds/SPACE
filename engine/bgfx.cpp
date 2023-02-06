#include <cassert>
#include <spdlog/spdlog.h>
#include <bgfx/bgfx.h>
#include "bgfx.hpp"
#include "window.hpp"
#include "window-backend-sfml.hpp"
#include "config.hpp"
#include "bgfx/cvars.hpp"
#include "bgfx/internal_components.hpp"

namespace engine::bgfx::detail {

////////////////////////////////////
////////////OTHER STUFF/////////////
////////////////////////////////////

void register_cvars(flecs::world&); //impl in engine/bgfx/cvars.cpp

static decltype(::bgfx::Resolution::reset) collect_reset_flags(flecs::world& world) {
  decltype(::bgfx::Resolution::reset) flags = BGFX_RESET_NONE;
  if (const std::int32_t* p_vsync = config::get_var<std::int32_t>(world, cvar::vsync); p_vsync && *p_vsync > 0) {
    flags |= BGFX_RESET_VSYNC;
  }
  if (const std::int32_t* p_maxanisotropy = config::get_var<std::int32_t>(world, cvar::maxanisotropy);
      p_maxanisotropy && *p_maxanisotropy > 0)
  {
    flags |= BGFX_RESET_MAXANISOTROPY;
  }
  if (const std::int32_t* p_capture = config::get_var<std::int32_t>(world, cvar::capture); p_capture && *p_capture > 0) {
    flags |= BGFX_RESET_CAPTURE;
  }
  if (const std::int32_t* p_flush_after_render = config::get_var<std::int32_t>(world, cvar::flush_after_render);
      p_flush_after_render && *p_flush_after_render > 0)
  {
    flags |= BGFX_RESET_FLUSH_AFTER_RENDER;
  }
  return flags;
}

static std::shared_ptr<BgfxLock> bgfx_init(flecs::world& world, std::shared_ptr<sf::WindowBase> window) {
  SPDLOG_TRACE("BGFX INIT");
  world.remove<UpdateResetFlags>(); //Потому что мы инициализируем с актуальными флагами

  ::bgfx::Init init;
  init.type = ::bgfx::RendererType::Direct3D11;
  init.platformData.nwh = window->getSystemHandle();
  init.resolution.width = window->getSize().x;
  init.resolution.height = window->getSize().y;
  init.resolution.reset  = collect_reset_flags(world);
  
  bool init_ok = ::bgfx::init(init);
  assert(init_ok);

  ::bgfx::setViewClear(0, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x505050ff, 1.0f, 0);

  SPDLOG_TRACE("BGFX INITED");
  return std::make_shared<BgfxLock>(window);
}

static bool is_cvar_enabled(flecs::world& world, std::string_view cvarname) {
  const std::int32_t* p_data = config::get_var<std::int32_t>(world, cvarname);
  if (p_data && *p_data > 0) {
    return true;
  } else {
    return false;
  }
}

////////////////////////////////////
/////////////SYSTEMS////////////////
////////////////////////////////////

static void InitSystem(flecs::iter it, const window_backend_sfml::MainWindowSFML* sfml_main_window) {
  assert(sfml_main_window->window);
  flecs::world world = it.world();
  world.set<BgfxContext>({
    .lock = bgfx_init(world, sfml_main_window->window)}
  );
}

static void BgfxFrameBegin(flecs::iter it, window::MainWindow* window) {
  std::uint32_t reset_flags = BGFX_RESET_NONE;
  if (const ResetFlags* p_flags = it.world().get<ResetFlags>(); p_flags) {
    reset_flags = p_flags->flags;
  }
  window->events.iterate([reset_flags](const window::Event& event) {
    if (event.is<window::event::Resized>()) {
      const window::event::Resized& resize_event = event.get<window::event::Resized>();
      SPDLOG_INFO("ON RESIZE");
      ::bgfx::reset(resize_event.width, resize_event.height, reset_flags);
    }
  });
  ::bgfx::setViewRect(0,0,0,window->width,window->height);
  ::bgfx::touch(0);
}

static void BgfxFrameEnd(flecs::iter it) {
  ::bgfx::frame();
}

static void UpdateReset(flecs::iter it, const window::MainWindow* window) {
  flecs::world world = it.world();
  auto reset_flags = collect_reset_flags(world);
  world.set<ResetFlags>({.flags = reset_flags});
  ::bgfx::reset(window->width, window->height, reset_flags);
}

static void UpdateDebugFlagsSystem(flecs::iter it) {
  SPDLOG_TRACE("Update debug flags");
  flecs::world world = it.world();
  world.remove<UpdateDebugFlags>();
  std::uint32_t flags = BGFX_DEBUG_NONE;
  if (detail::is_cvar_enabled(world, cvar::debug_wireframe)) {
    flags |= BGFX_DEBUG_WIREFRAME;
  }
  if (detail::is_cvar_enabled(world, cvar::debug_ihf)) {
    flags |= BGFX_DEBUG_IFH;
  }
  if (detail::is_cvar_enabled(world, cvar::debug_stats)) {
    flags |= BGFX_DEBUG_STATS;
  }
  if (detail::is_cvar_enabled(world, cvar::debug_text)) {
    SPDLOG_CRITICAL("NBOOOOOOOOOOOOOOOOOOOP");
    flags |= BGFX_DEBUG_TEXT;
  }
  if (detail::is_cvar_enabled(world, cvar::debug_profiler)) {
    flags |= BGFX_DEBUG_PROFILER;
  }
  ::bgfx::setDebug(flags);
}

} //namespace engine::bgfx::detail

engine::Bgfx::Bgfx(flecs::world& world): reset_flags(BGFX_RESET_NONE) {
  using namespace ::engine::bgfx;
  world.import<Window>();
  world.import<WindowBackendSfml>();
  world.import<Config>();
  world.module<Bgfx>("bgfx");

  //components
  world.component<BgfxContext>();
  detail::register_internal_components(world);

  //cvars
  detail::register_cvars(world);

  //systems
  world.system<const window_backend_sfml::MainWindowSFML>("system::InitSystem")
    .arg(1).singleton()
    .without<BgfxContext>().singleton()
    .iter(detail::InitSystem);

  world.system<window::MainWindow>("system::BgfxFrameBegin")
    .kind(flecs::PreStore)
    .arg(1).singleton()
    .with<BgfxContext>().singleton()
    .iter(detail::BgfxFrameBegin);

  world.system("system::BgfxFrameEnd")
    .kind(flecs::PostFrame)
    .with<BgfxContext>().singleton()
    .iter(detail::BgfxFrameEnd);

  world.system<const window::MainWindow>("system::UpdateReset")
    .kind(flecs::PostFrame)
    .arg(1).singleton()
    .with<BgfxContext>().singleton()
    .with<detail::UpdateResetFlags>().singleton()
    .iter(detail::UpdateReset);

  world.system("system::UpdateDebugFlags")
    .kind(flecs::PostFrame)
    .with<BgfxContext>().singleton()
    .with<detail::UpdateDebugFlags>().singleton()
    .iter(detail::UpdateDebugFlagsSystem);

}