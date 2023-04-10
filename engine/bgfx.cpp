#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <algorithm> //for lovercase of cvar render backend (std::transform)
#include <cctype>  //for lovercase of cvar render backend (std::tolower)
#include <spdlog/spdlog.h>
#include <bgfx/bgfx.h>
#include "window.hpp"
#include "window-backend-sfml.hpp"
#include "cvar.hpp"
#include "bgfx.hpp"
#include "bgfx/internal_components.hpp"

#include <bx/bx.h>

//see init.platformData.ndt in bgfx_init()
#if BX_PLATFORM_LINUX
  #include <X11/Xlib.h>
#endif

namespace engine::bgfx::detail {

////////////////////////////////////
////////////OTHER STUFF/////////////
////////////////////////////////////

void register_cvars(flecs::world&); //impl in engine/bgfx/cvars.cpp

static decltype(::bgfx::Resolution::reset) collect_reset_flags(flecs::world& world) {
  decltype(::bgfx::Resolution::reset) flags = BGFX_RESET_NONE;
  if (cvar::vsync::read(world)) {
    flags |= BGFX_RESET_VSYNC;
  }
  if (cvar::maxanisotropy::read(world)) {
    flags |= BGFX_RESET_MAXANISOTROPY;
  }
  if (cvar::capture::read(world)) {
    flags |= BGFX_RESET_CAPTURE;
  }
  if (cvar::flush_after_render::read(world)) {
    flags |= BGFX_RESET_FLUSH_AFTER_RENDER;
  }
  return flags;
}

static std::shared_ptr<BgfxLock> bgfx_init(flecs::world& world, std::shared_ptr<sf::WindowBase> window) {
  SPDLOG_TRACE("BGFX INIT");
  world.remove<UpdateResetFlags>(); //Потому что мы инициализируем с актуальными флагами

  ::bgfx::Init init;
  //choose render backend
  {
    std::string cvar_backend = cvar::render_backend::read(world);
    std::transform(cvar_backend.begin(), cvar_backend.end(), cvar_backend.begin(), [](unsigned char ch){
      return static_cast<char>(std::tolower(ch));
    });
    if (cvar_backend == "noop") {
      init.type = ::bgfx::RendererType::Noop;
    } else if (cvar_backend == "agc") {
      init.type = ::bgfx::RendererType::Agc;
    } else if (cvar_backend == "direct3d9") {
      init.type = ::bgfx::RendererType::Direct3D9;
    } else if (cvar_backend == "direct3d11") {
      init.type = ::bgfx::RendererType::Direct3D11;
    } else if (cvar_backend == "direct3d12") {
      init.type = ::bgfx::RendererType::Direct3D12;
    } else if (cvar_backend == "gnm") {
      init.type = ::bgfx::RendererType::Gnm;
    } else if (cvar_backend == "metal") {
      init.type = ::bgfx::RendererType::Metal;
    } else if (cvar_backend == "nvn") {
      init.type = ::bgfx::RendererType::Nvn;
    } else if (cvar_backend == "opengles") {
      init.type = ::bgfx::RendererType::OpenGLES;
    } else if (cvar_backend == "opengl") {
      init.type = ::bgfx::RendererType::OpenGL;
    } else if (cvar_backend == "vulkan") {
      init.type = ::bgfx::RendererType::Vulkan;
    } else if (cvar_backend == "webgpu") {
      init.type = ::bgfx::RendererType::WebGPU;
    } else {
      SPDLOG_WARN("Unknown render backend - '{}'. Using default 'vulkan' by default", cvar_backend);
      init.type = ::bgfx::RendererType::Vulkan;
    }
  }
  init.platformData.nwh = reinterpret_cast<void*>(window->getSystemHandle());
#if BX_PLATFORM_LINUX
  init.platformData.ndt = XOpenDisplay(nullptr);
  if (!init.platformData.ndt) {
    SPDLOG_CRITICAL("XOpenDisplay failed");
    std::exit(EXIT_FAILURE);
  }
#endif
  init.resolution.width = window->getSize().x;
  init.resolution.height = window->getSize().y;
  init.resolution.reset  = collect_reset_flags(world);
  
  bool init_ok = ::bgfx::init(init);
  assert(init_ok);

  SPDLOG_TRACE("BGFX INITED");
  return std::make_shared<BgfxLock>(window);
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
  if (cvar::debug_wireframe::read(world)) {
    flags |= BGFX_DEBUG_WIREFRAME;
  }
  if (cvar::debug_ihf::read(world)) {
    flags |= BGFX_DEBUG_IFH;
  }
  if (cvar::debug_stats::read(world)) {
    flags |= BGFX_DEBUG_STATS;
  }
  if (cvar::debug_text::read(world)) {
    flags |= BGFX_DEBUG_TEXT;
  }
  if (cvar::debug_profiler::read(world)) {
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
  if (cvar::mainwindow_clear_depth::read(world)) {
    clear_flags |= BGFX_CLEAR_DEPTH;
  }
  if (cvar::mainwindow_clear_stencil::read(world)) {
    clear_flags |= BGFX_CLEAR_STENCIL;
  }

  //depth
  float clear_depth = cvar::mainwindow_clear_depth_value::read(world);

  //stencil
  std::uint8_t clear_stencil = cvar::mainwindow_clear_stencil_value::read(world);

  //color
  std::uint32_t clear_color = cvar::mainwindow_clear_color_value::read(world);
  
  ::bgfx::setViewClear(0, clear_flags, clear_color, clear_depth, clear_stencil);
}

} //namespace engine::bgfx::detail

engine::Bgfx::Bgfx(flecs::world& world):
    reset_flags(BGFX_RESET_NONE)
{
  using namespace ::engine::bgfx;
  world.import<Window>();
  world.import<WindowBackendSfml>();
  world.import<Cvar>();
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