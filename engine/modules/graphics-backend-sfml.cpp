#include <spdlog/spdlog.h>
#include "graphics-backend-sfml.hpp"
#include "window.hpp"
#include "geometry.hpp"
#include "graphics.hpp"
#include "window-backend-sfml.hpp"
#include "transform.hpp"

namespace engine::graphics_backend_sfml::detail {

void AddRenderTarget(flecs::entity e) {
  const window_backend_sfml::MainWindowSFML* sfml_window = e.world().get<window_backend_sfml::MainWindowSFML>();
  e.set<RenderTarget>({.target = sfml_window->window});
}

void RenderSystem(flecs::entity e,
                  const transform::Transform2& camera_world_transform,
                  const transform::Transform2& drawable_world_transform) 
{
  SPDLOG_INFO("RENDER IT - {}", e.doc_name());

}

} //engine::graphics_backend_sfml::detail

namespace engine {
using namespace graphics_backend_sfml;

GraphicsBackendSFML::GraphicsBackendSFML(flecs::world& world) {
  world.import<Window>();
  world.import<Geometry>();
  world.import<Graphics>();
  world.import<Transform>();
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

  //world.system<const transform::Transform2&, const transform::Transform2&>("system::RenderSystem")
  //  .no_readonly()
  //  .term_at(1).up<graphics::OnRender>()
    //.parent
  //  .each(detail::RenderSystem);
}

} //namespace engine