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
  init.platformData.ndt = window->getSystemHandle();
  init.resolution.width = window->getSize().x;
  init.resolution.height = window->getSize().y;
  
  bool init_ok = ::bgfx::init(init);

  assert(init_ok);


  return std::make_shared<BgfxLock>(window);
}

////////////////////////////////////
/////////////SYSTEMS////////////////
////////////////////////////////////

static void InitSystem(flecs::iter it, const window_backend_sfml::MainWindowSFML* sfml_main_window) {
  assert(sfml_main_window->window);
  SPDLOG_INFO("BOP");
  it.world().set<BgfxContext>({.lock = bgfx_init(sfml_main_window->window)});

  ::bgfx::setViewClear(0, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0xff3030ff, 1.0f, 0);
  //::bgfx::Caps
}

static void BgfxFrameBegin(flecs::iter it, const window::MainWindow* window) {
  ::bgfx::setViewRect(0,0,0,window->width,window->height);
  ::bgfx::touch(0);
}

static void BgfxFrameEnd(flecs::iter it) {
  SPDLOG_INFO("BOOOOP");
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

  world.system<const window::MainWindow>("system::BgfxFrameBegin")
    .kind(flecs::PreStore)
    .arg(1).singleton()
    .iter(detail::BgfxFrameBegin);

  world.system("system::BgfxFrameEnd")
    .kind(flecs::PostFrame)
    .iter(detail::BgfxFrameEnd);
}
