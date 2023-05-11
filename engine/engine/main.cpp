#include <flecs.h>
#include <spdlog/spdlog.h>
#include "setup_spdlog.hpp"

#include "../window.hpp"
#include "../window-backend-sfml.hpp"
#include "../graphics.hpp"
#include "../geometry.hpp"
#include "../graphics-backend-sfml.hpp"
#include "../transform.hpp"


int main(int argc, char const *argv[]) {
  engine::setup_spdlog();
  flecs::world world;
  world.set_target_fps(60);
  world.set_threads(2);
  world.import<flecs::monitor>();
  world.import<engine::Window>();
  world.import<engine::WindowBackendSfml>();

  world.set<engine::window::MainWindowInit>({.width = 1000, .height = 600, .init_render_window = true});
  world.add<engine::window::ExitOnClosed>();
  world.set<engine::window::ExitButton>({.key = engine::window::Key::Escape});

  world.import<engine::Geometry>();
  world.import<engine::Graphics>();
  world.import<engine::Transform>();
  world.import<engine::GraphicsBackendSFML>();


  flecs::entity camera = world.entity()
    .set_doc_name("Main Camera")
    .add<engine::geometry::Rectangle>()
    .add<engine::graphics::Camera>()
    .set<engine::graphics::MainWindowCamera>({
      .camera_size = {7, 7}
    })
    .set<engine::transform::Position2>({
      .x = 0,
      .y = 0
    })
    .add<engine::transform::Transform2>();

  flecs::entity drawable = world.entity()
    .set_doc_name("drawable")
    .set<engine::geometry::Square>({.size=1})
    .add<engine::graphics_backend_sfml::Square>()
    //.set<engine::transform::Rotation2>({.angle = 30.30})
    //.set<engine::transform::Scale2>({.x=2,.y=2})
    .set<engine::transform::Position2>({.x=0,.y=0})
    .add<engine::transform::Transform2>()
    .set<engine::graphics::Color>(engine::graphics::color::brown)
    .add<engine::graphics::RenderedBy>(camera);


  world.system<engine::window_backend_sfml::MainWindowSFML_RenderWindow>("win clear")
    .kind(flecs::PreStore)
    .each([](flecs::entity e, engine::window_backend_sfml::MainWindowSFML_RenderWindow& renderwindow) {
      renderwindow.window->clear(sf::Color(0x444444FF));
    });


  world.system<engine::window_backend_sfml::MainWindowSFML_RenderWindow>("swap buffers")
    .kind(flecs::PostFrame)
    .each([](flecs::entity e, engine::window_backend_sfml::MainWindowSFML_RenderWindow& renderwindow) {
      renderwindow.window->display();
    });


  
  world.app().enable_rest().run();
  return 0;
}