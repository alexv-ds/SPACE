#include <flecs.h>
#include <spdlog/spdlog.h>
#include "setup_spdlog.hpp"

#include "modules/window.hpp"
#include "modules/window-backend-sfml.hpp"
#include "modules/filesystem.hpp"
#include "modules/filesystem-backend-stdlib.hpp"
#include "modules/transform.hpp"
#include "modules/graphics.hpp"
#include "modules/geometry.hpp"
#include "modules/graphics-backend-sfml.hpp"

int main(int argc, char const *argv[]) {
  engine::setup_spdlog();
  flecs::world world;
  world.set_target_fps(40);
  world.set_threads(4);
  world.import<flecs::monitor>();

  //world.import<engine::Window>();
  world.import<engine::WindowBackendSfml>();
  world.set<engine::window::MainWindowInit>({});
  world.import<engine::Filesystem>();
  world.import<engine::FilesystemBackendStdlib>();
  world.import<engine::Transform>();
  world.import<engine::Graphics>();
  world.import<engine::GraphicsBackendSFML>();
  world.import<engine::Geometry>();

  world.system<const engine::window_backend_sfml::MainWindowSFML>("testsys")
    .kind(flecs::OnStore)
    .arg(1).singleton()
    .iter([](flecs::iter it, const engine::window_backend_sfml::MainWindowSFML* window_component) {
      //sf::CircleShape shape(50.f);
      //shape.setFillColor(sf::Color(150, 50, 250, 128));
      //window_component->window->draw(shape);
    });



  flecs::entity camera = world.entity()
    .set_doc_name("Main Camera")
    .add<engine::geometry::Rectangle>()
    .add<engine::graphics::Camera>()
    .set<engine::graphics::MainWindowCamera>({
      .camera_size = {7, 7}
    })
    .set<engine::transform::Position2>({
      .x = 1,
      .y = 1
    });

  flecs::entity drawable = world.entity()
    .set_doc_name("drawable")
    .set<engine::geometry::Square>({.size=1})
    .add<engine::graphics_backend_sfml::Square>()
    //.set<engine::transform::Rotation2>({.angle = 30.30})
    //.set<engine::transform::Scale2>({.x=2,.y=2})
    .set<engine::transform::Position2>({.x=1,.y=1})
    .add<engine::graphics::RenderedBy>(camera);

  world.app().enable_rest().run();
  return 0;
}
