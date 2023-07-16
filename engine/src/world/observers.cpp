#include <flecs.h>
#include <engine/lib/log.hpp>
#include <engine/world/transform.hpp>
#include <engine/world/world-object.hpp>
#include <engine/world/spatial.hpp>
#include "../modules.hpp"

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

static void OnAddHandleIntersections(flecs::entity entity) {
  entity.add<InitIntersections>();
}

void init_observers(flecs::world& world) {
  [[maybe_unused]] auto scope = world.scope(world.entity("observer"));
  world.observer("MonitorPosition")
    .event(flecs::Monitor)
    .with<Position>()
    .each(MonitorPosition);

  world.observer("OnAddHandleIntersections")
    .event(flecs::OnAdd)
    .with<HandleIntersections>()
    .each(OnAddHandleIntersections);
}

} //end of engine::world
