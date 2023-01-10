#include "graphics-backend-sfml.hpp"
#include "window.hpp"
#include "geometry.hpp"
#include "graphics.hpp"
#include "window-backend-sfml.hpp"

namespace engine::graphics_backend_sfml::detail {

void AddRenderTarget(flecs::entity e) {
  const window_backend_sfml::MainWindowSFML* sfml_window = e.world().get<window_backend_sfml::MainWindowSFML>();
  e.set<RenderTarget>({.target = sfml_window->window});
}

} //engine::graphics_backend_sfml::detail

namespace engine {
using namespace graphics_backend_sfml;

GraphicsBackendSFML::GraphicsBackendSFML(flecs::world& world) {
  world.import<Window>();
  world.import<Geometry>();
  world.import<Graphics>();
  world.import<WindowBackendSfml>();

  world.module<GraphicsBackendSFML>("graphics_backend_sfml");

  //components
  world.component<RenderTarget>();

  //systems 
  world.system("system::AddRenderTarget")
    .with<window_backend_sfml::MainWindowSFML>().singleton()
    .with<graphics::MainWindowCamera>()
    .without<RenderTarget>()
    .each(detail::AddRenderTarget);

}

} //namespace engine