#include <spdlog/spdlog.h>
#include "setup_spdlog.hpp"

#include "../window.hpp"
#include "../window-backend-sfml.hpp"
#include "../cvar.hpp"
#include "../bgfx.hpp"

#include <bgfx/bgfx.h>

int main(int argc, char const *argv[]) {
  engine::setup_spdlog();
  flecs::world world;
  world.set_target_fps(60);
  world.set_threads(2);
  world.import<flecs::monitor>();
  world.import<engine::Window>();
  world.import<engine::WindowBackendSfml>();
  world.import<engine::Bgfx>();
  world.set<engine::window::MainWindowInit>({.width = 1000, .height = 600});
  world.add<engine::window::ExitOnClosed>();
  world.set<engine::window::ExitButton>({.key = engine::window::Key::Escape});

  world.import<engine::Cvar>();

  //engine::cvar::update<bool>(world, engine::bgfx::cvar::debug_stats, false);
  engine::cvar::update<bool>(world, engine::bgfx::cvar::debug_text, true);
  engine::cvar::update<std::uint32_t>(world, engine::bgfx::cvar::mainwindow_clear_color_value, 0x444444FF);

  world.system("DEBUGTEXT")
    .kind(flecs::OnStore)
    .with<engine::bgfx::BgfxContext>().singleton()
    .iter([](flecs::iter it) {
      bgfx::dbgTextClear();
      bgfx::dbgTextPrintf(0, 0, 0x0f, "Hello World");
    });


  
  world.app().enable_rest().run();
  return 0;
}