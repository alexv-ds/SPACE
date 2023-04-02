#include <spdlog/spdlog.h>
#include "setup_spdlog.hpp"

#include "../window.hpp"
#include "../window-backend-sfml.hpp"
#include "../cvar.hpp"

void foo(int&& arg1) {

}

int main(int argc, char const *argv[]) {
  engine::setup_spdlog();
  flecs::world world;
  world.set_target_fps(60);
  world.set_threads(2);
  world.import<flecs::monitor>();
  world.import<engine::Window>();
  world.import<engine::WindowBackendSfml>();
  world.set<engine::window::MainWindowInit>({.width = 1000, .height = 600});
  world.add<engine::window::ExitOnClosed>();
  world.set<engine::window::ExitButton>({.key = engine::window::Key::Escape});

  engine::cvar::register_type<std::int32_t>(world, "cvar_type::int32");

  engine::cvar::create<std::int32_t>(world, "mycvar", 123);
  

  
  world.app().enable_rest().run();
  return 0;
}