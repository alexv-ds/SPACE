#include <format>
#include <spdlog/spdlog.h>
#include <flecs.h>
#include "../engine/setup_spdlog.hpp"


//using namespace game;

int main() {
  engine::setup_spdlog();
  flecs::world world;
  world.set_threads(4);
  world.set_target_fps(60);
  world.import<flecs::monitor>();

  world.app().enable_rest().run();
}