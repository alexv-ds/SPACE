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

  world.import<engine::Window>();
  world.import<engine::WindowBackendSfml>();
  world.import<engine::Filesystem>();
  world.import<engine::FilesystemBackendStdlib>();
  world.import<engine::Transform>();
  world.set<engine::window::MainWindowInit>({});
  world.import<engine::Graphics>();
  world.import<engine::GraphicsBackendSFML>();
  world.import<engine::Geometry>();

  flecs::entity drawable = world.entity()
    .set_doc_name("drawable")
    .set<engine::geometry::Square>({.size=1})
    .set<engine::transform::Position2>({.x=1,.y=1});

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
    .add<engine::graphics::OnRender>(drawable);

  world.app().enable_rest().run();
  return 0;
}
