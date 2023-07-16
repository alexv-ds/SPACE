#include <memory>
#include <engine/world/world.hpp>
#include "../modules.hpp"

namespace engine {

namespace world {
void init_components(flecs::world&);
void init_systems(flecs::world&);
void init_observers(flecs::world&);
}

World::World(flecs::world& world) {
  world.import<flecs::units>();
  world.import<Reflection>();
  world.module<World>("world");
  world::init_components(world);
  world::init_observers(world);
  world::init_systems(world);
}

} //end of namespace engine

