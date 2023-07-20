#include <flecs.h>
#include <engine/lib/log.hpp>
#include <engine/world/transform.hpp>
#include <engine/world/world-object.hpp>
#include <engine/world/spatial.hpp>
#include "../modules.hpp"

namespace engine::world {

static void MonitorPositionOld(flecs::iter& it, std::size_t i) {
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


template <class T>
static void MonitorGlobalRelation(flecs::iter& it, std::size_t i) {
  if (it.event() == flecs::OnAdd) {
    it.entity(i).add<T, Global>();
  } else if (it.event() == flecs::OnRemove) {
    it.entity(i).remove<T, Global>();
  }
}

void init_observers(flecs::world& world) {
  [[maybe_unused]] auto scope = world.scope(world.entity("observer"));
  world.observer("MonitorPositionOld")
    .event(flecs::Monitor)
    .with<Position>()
    .each(MonitorPositionOld);

  world.observer("OnAddHandleIntersections")
    .event(flecs::OnAdd)
    .with<HandleIntersections>()
    .each(OnAddHandleIntersections);

  world.observer("MonitorPosition")
    .event(flecs::Monitor)
    .with<Position>()
    .each(MonitorGlobalRelation<Position>);

  world.observer("MonitorScale")
    .event(flecs::Monitor)
    .with<Scale>()
    .each(MonitorGlobalRelation<Scale>);

  world.observer("MonitorRotation")
    .event(flecs::Monitor)
    .with<Rotation>()
    .each(MonitorGlobalRelation<Rotation>);
}

} //end of engine::world
