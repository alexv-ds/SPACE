//#include <flecs.h>
#include <spdlog/spdlog.h>
#include "bgfx/bgfx.h"
#include "setup_spdlog.hpp"

#include "../window.hpp"
#include "../window-backend-sfml.hpp"
#include "../bgfx.hpp"
#include "../config.hpp"

int main(int argc, char const *argv[]) {
  engine::setup_spdlog();
  flecs::world world;
  world.set_target_fps(60);
  world.set_threads(2);
  world.import<flecs::monitor>();
  world.import<engine::Window>();
  world.import<engine::WindowBackendSfml>();
  world.import<engine::Bgfx>();

  world.set<engine::window::MainWindowInit>({
    .width = 1000,
    .height = 600
  });
  world.add<engine::window::ExitOnClosed>();
  world.set<engine::window::ExitButton>({
    .key = engine::window::Key::Escape
  });

  engine::config::update_var(world, engine::bgfx::cvar::debug_stats, 0);
  engine::config::update_var(world, engine::bgfx::cvar::debug_text, 1);

  world.system()
    .kind(flecs::OnStore)
    .with<::engine::bgfx::BgfxContext>().singleton()
    .iter([](flecs::iter it) {
      ::bgfx::dbgTextClear();
      ::bgfx::dbgTextPrintf(1,1,0,"YHAHATBLE");
    });


  /*config::create_typed_var_listener(world, bgfx::cvar::debug_stats, "mylistener", [](flecs::world& world, const std::int32_t& value) {

  });*/

  world.app().enable_rest().run();
  
  return 0;
}