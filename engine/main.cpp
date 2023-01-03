#include <flecs.h>
#include <spdlog/spdlog.h>
#include "setup_spdlog.hpp"

#include "modules/window.hpp"
#include "modules/window-backend-sfml.hpp"
#include "modules/filesystem.hpp"
#include "modules/filesystem-backend-stdlib.hpp"

int main(int argc, char const *argv[]) {
  engine::setup_spdlog();
  flecs::world world;
  world.set_target_fps(5);
  world.set_threads(4);
  world.import<flecs::monitor>();

  world.import<engine::Window>();
  world.import<engine::WindowBackendSfml>();
  world.import<engine::Filesystem>();
  world.import<engine::FilesystemBackendStdlib>();

  //world.set<engine::window::MainWindowInit>({});
  world.entity().set<engine::filesystem::ReadFileRequest>({.path="CMakeLists.txt"});
  world.system<const engine::filesystem::ReadFileResponse>()
    .each([](flecs::entity e, const engine::filesystem::ReadFileResponse& res) {
      std::string str(reinterpret_cast<const char*>(res.data.data()), res.data.size());
      SPDLOG_DEBUG("{}", std::move(str));
      e.destruct();
    });

  world.app().enable_rest().run();
  return 0;
}
