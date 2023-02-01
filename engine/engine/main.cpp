#include <flecs.h>
#include <spdlog/spdlog.h>
#include "setup_spdlog.hpp"

//#include "modules/window.hpp"
//#include "modules/window-backend-sfml.hpp"

int main(int argc, char const *argv[]) {
  engine::setup_spdlog();
  flecs::world world;
  world.set_target_fps(60);
  world.set_threads(4);
  world.import<flecs::monitor>();



  world.app().enable_rest().run();
  return 0;
}
