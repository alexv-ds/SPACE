#include <engine/engine.hpp>
#include "debug.hpp"

namespace engine {

std::shared_ptr<flecs::world> create_world(int argc, char* argv[]) {
  return create_world();
}

std::shared_ptr<flecs::world> create_world() {
  std::shared_ptr world = std::make_shared<flecs::world>();
  world->set_threads(2);
  world->import<Debug>();
  return world;
}

bool update_world(flecs::world& world, const float dt) {
  return world.progress();
}

  
} //namespace engine

