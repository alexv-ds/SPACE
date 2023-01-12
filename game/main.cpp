#include <spdlog/spdlog.h>
#include <flecs.h>
#include "../engine/setup_spdlog.hpp"
#include "powernet.hpp"

int main() {
  engine::setup_spdlog();
  flecs::world world;
  world.import<game::Powernet>();
  world.app().enable_rest().run();
}