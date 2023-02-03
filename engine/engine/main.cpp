//#include <flecs.h>
#include <spdlog/spdlog.h>
#include "setup_spdlog.hpp"

#include "../window.hpp"
#include "../window-backend-sfml.hpp"
#include "../bgfx.hpp"

using namespace engine;

int main(int argc, char const *argv[]) {
  engine::setup_spdlog();
  flecs::world world;
  world.set_target_fps(60);
  world.set_threads(2);
  world.import<flecs::monitor>();
  world.import<Window>();
  world.import<WindowBackendSfml>();
  world.import<Bgfx>();

  world.add<window::MainWindowInit>();
  world.add<window::ExitOnClosed>();
  world.set<window::ExitButton>({
    .key = window::Key::Escape
  });

  world.app().enable_rest().run();
  return 0;
}
