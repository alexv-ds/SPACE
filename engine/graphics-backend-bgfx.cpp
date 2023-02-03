#include <spdlog/spdlog.h>
#include "window.hpp"
#include "window-backend-sfml.hpp"
#include "graphics-backend-bgfx.hpp"

namespace engine::graphics_backend_bgfx::detail {

////////////////////////////////////
////////////OTHER STUFF/////////////
////////////////////////////////////

static std::shared_ptr<BgfxLock> bgfx_init (std::shared_ptr<sf::WindowBase> window) {
  SPDLOG_DEBUG("Init BGFX");
  
  return nullptr;
}

////////////////////////////////////
/////////////SYSTEMS////////////////
////////////////////////////////////

void InitObserver(flecs::iter it, const window_backend_sfml::MainWindowSFML* sfml_main_window) {
  assert(sfml_main_window->window);
  it.world().set<Bgfx>({.lock = bgfx_init(sfml_main_window->window)});
}

} //namespace engine::graphics_backend_bgfx::detail


namespace engine {
using namespace graphics_backend_bgfx;

GraphicsBackendBGFX::GraphicsBackendBGFX(flecs::world& world) {
  world.import<Window>();
  world.import<WindowBackendSfml>();
  world.module<GraphicsBackendBGFX>("graphics_backend_bgfx");

}

} //namespace engine