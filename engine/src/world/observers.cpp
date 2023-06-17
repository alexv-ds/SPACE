#include <flecs.h>
#include <engine/world/transform.hpp>

namespace engine::world {

static void MonitorPosition(flecs::iter& it, std::size_t i) {
  flecs::entity e = it.entity(i);
  flecs::entity_t event = it.event();
  if (event == flecs::OnAdd) {
    e.add<Transform>();
  } else if (event == flecs::OnRemove) {
    e.remove<Transform>();
  }
}

void init_observers(flecs::world& world) {
  [[maybe_unused]] auto scope = world.scope(world.entity("observer"));
  world.observer("MonitorPosition")
    .event(flecs::Monitor)
    .with<Position>()
    .each(MonitorPosition);
}

} //end of engine::world
