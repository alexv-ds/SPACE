#include <cassert>
#include <spdlog/spdlog.h>
#include <bgfx/bgfx.h>
#include "bgfx.hpp"
#include "window.hpp"
#include "window-backend-sfml.hpp"

namespace engine::bgfx::detail {

////////////////////////////////////
////////////OTHER STUFF/////////////
////////////////////////////////////

static std::shared_ptr<BgfxLock> bgfx_init(std::shared_ptr<sf::WindowBase> window) {
  SPDLOG_TRACE("BGFX INIT");
  ::bgfx::Init init;
  init.type = ::bgfx::RendererType::Direct3D11;
  init.platformData.nwh = window->getSystemHandle();
  init.resolution.width = window->getSize().x;
  init.resolution.height = window->getSize().y;
  //init.resolution.reset  = BGFX_RESET_VSYNC;
  
  bool init_ok = ::bgfx::init(init);
  assert(init_ok);

  ::bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_STATS);
  ::bgfx::setViewClear(0, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x505050ff, 1.0f, 0);

  SPDLOG_TRACE("BGFX INITED");
  return std::make_shared<BgfxLock>(window);
}

////////////////////////////////////
/////////////SYSTEMS////////////////
////////////////////////////////////

static void InitSystem(flecs::iter it, const window_backend_sfml::MainWindowSFML* sfml_main_window) {
  assert(sfml_main_window->window);
  SPDLOG_INFO("BOP");
  it.world().set<BgfxContext>({.lock = bgfx_init(sfml_main_window->window)});
}

static void BgfxFrameBegin(flecs::iter it, window::MainWindow* window) {
  window->events.iterate([](const window::Event& event) {
    if (event.is<window::event::Resized>()) {
      const window::event::Resized& resize_event = event.get<window::event::Resized>();
      SPDLOG_INFO("ON RESIZE");
      ::bgfx::reset(resize_event.width, resize_event.height, BGFX_RESET_VSYNC);
    }
  });

  ::bgfx::setViewRect(0,0,0,window->width,window->height);

}

static void BgfxFrameEnd(flecs::iter it) {
  ::bgfx::touch(0);
  ::bgfx::frame();
}

} //namespace engine::bgfx::detail

engine::Bgfx::Bgfx(flecs::world& world) {
  using namespace ::engine::bgfx;
  world.import<Window>();
  world.import<WindowBackendSfml>();
  world.module<Bgfx>("bgfx");

  //components
  world.component<BgfxContext>();

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

}