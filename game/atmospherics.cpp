#include "atmospherics.hpp"

namespace game {
using namespace atmospherics;

Atmospherics::Atmospherics(flecs::world& world) {
  world.module<Atmospherics>("atmospherics");
}

} //namespace game
