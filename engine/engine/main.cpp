//#include <flecs.h>
#include <spdlog/spdlog.h>
#include "bgfx/bgfx.h"
#include "setup_spdlog.hpp"

#include "../window.hpp"
#include "../window-backend-sfml.hpp"
#include "../bgfx.hpp"
#include "../config.hpp"
#include "../config2.hpp"


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

  engine::config::update_var(world, engine::bgfx::cvar::debug_stats, 1);
  //engine::config::update_var(world, engine::bgfx::cvar::debug_text, 1);
  engine::config::update_var(world, engine::bgfx::cvar::mainwindow_clear_color_value, "0x4f4f4fff");

  world.system("debug draw")
    .kind(flecs::OnStore)
    .with<::engine::bgfx::BgfxContext>().singleton()
    .iter([](flecs::iter it) {
      //SPDLOG_INFO("TICK");
      //::bgfx::setDebug(BGFX_DEBUG_TEXT);
      ::bgfx::dbgTextClear();
      ::bgfx::dbgTextPrintf(1,1,0,"YHAHATBLE");
    });


  world.import<engine::Config2>();
  engine::config2::create_var<engine::config2::type::Int32>(world.entity("my_cvar"), 123);


  world.app().enable_rest().run();
  
  return 0;
}