#include <cassert>
#include <cstdio>
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
  window->events.iterate([&it](const window::Event& event) {
    if (event.is<window::event::Resized>()) {
      std::uint32_t reset_flags = BGFX_RESET_NONE;
      if (const ResetFlags* p_flags = it.world().get<ResetFlags>(); p_flags) {
        reset_flags = p_flags->flags;
      }
      const window::event::Resized& resize_event = event.get<window::event::Resized>();
      SPDLOG_TRACE("ON RESIZE");
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
    flags |= BGFX_DEBUG_TEXT;
  }
  if (detail::is_cvar_enabled(world, cvar::debug_profiler)) {
    flags |= BGFX_DEBUG_PROFILER;
  }
  ::bgfx::setDebug(flags);
}

void System_UpdateClearData(flecs::iter it, Bgfx* bgfx_module) {
  SPDLOG_TRACE("Update Clear Data");
  flecs::world world = it.world();
  world.remove<UpdateClearData>();

  //clear flags
  std::uint16_t clear_flags = BGFX_CLEAR_COLOR;
  if (is_cvar_enabled(world, bgfx::cvar::mainwindow_clear_depth)) {
    clear_flags |= BGFX_CLEAR_DEPTH;
  }
  if (is_cvar_enabled(world, bgfx::cvar::mainwindow_clear_stencil)) {
    clear_flags |= BGFX_CLEAR_STENCIL;
  }

  //depth
  float clear_depth = 0.0f;
  if (const float* depth_value =
        config::get_var<float>(world, bgfx::cvar::mainwindow_clear_depth_value); depth_value)
  {
    clear_depth = *depth_value;
  }

  //stencil
  std::uint8_t clear_stencil = 0;
  if (const std::int32_t* stencil_value =
        config::get_var<std::int32_t>(world, bgfx::cvar::mainwindow_clear_stencil_value); stencil_value)
  {
    if (*stencil_value < 0 || *stencil_value > 255) {
      SPDLOG_ERROR("{} is not in range from 0 to 255. Current value: {}", bgfx::cvar::mainwindow_clear_stencil_value, *stencil_value);
    } else {
      clear_stencil = static_cast<std::uint8_t>(*stencil_value);
    }
  }

  //color
  std::uint32_t clear_color;
  static_assert(sizeof(std::uint32_t) == sizeof(unsigned long)); //Потому что мы используем strtoul() для конверта строки в uint32
  if (const std::string* color_value =
        config::get_var<std::string>(world, bgfx::cvar::mainwindow_clear_color_value); color_value)
  {
    char* end = nullptr;
    clear_color = std::strtoul(color_value->c_str(), &end, 16);
  }


  ::bgfx::setViewClear(0, clear_flags, clear_color, clear_depth, clear_stencil);
}

} //namespace engine::bgfx::detail

engine::Bgfx::Bgfx(flecs::world& world):
    reset_flags(BGFX_RESET_NONE)
{
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
    .kind(flecs::PostFrame)
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
  
  world.system<Bgfx>("system::UpdateClearData")
    .kind(flecs::PostFrame)
    .with<BgfxContext>().singleton()
    .with<detail::UpdateClearData>().singleton()
    .arg(1).singleton()
    .iter(detail::System_UpdateClearData);
}