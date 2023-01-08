#include <flecs.h>
#include <spdlog/spdlog.h>
#include "setup_spdlog.hpp"

#include "modules/window.hpp"
#include "modules/window-backend-sfml.hpp"
#include "modules/filesystem.hpp"
#include "modules/filesystem-backend-stdlib.hpp"
#include "modules/transform.hpp"
#include "modules/opengl.hpp"

int main(int argc, char const *argv[]) {
  engine::setup_spdlog();
  flecs::world world;
  world.set_target_fps(4);
  world.set_threads(4);
  world.import<flecs::monitor>();

  world.import<engine::Window>();
  world.import<engine::WindowBackendSfml>();
  world.import<engine::Filesystem>();
  world.import<engine::FilesystemBackendStdlib>();
  world.import<engine::Transform>();
  world.set<engine::window::MainWindowInit>({});

  world.entity().set<engine::opengl::ShaderProgramLoader>({
    .vs_path = "resources/shader.vs",
    .fs_path = "resources/shader.fs",
  });


  world.app().enable_rest().run();
  return 0;
}
