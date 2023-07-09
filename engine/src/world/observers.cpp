#include <flecs.h>
#include <engine/lib/log.hpp>
#include <engine/world/transform.hpp>
#include <engine/world/world-object.hpp>
#include <engine/world/spatial.hpp>
#include "spatial/component.hpp"
#include "spatial/bbox_calculation.hpp"
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

static void MonitorWorldObject(flecs::iter& it, std::size_t i, const WorldObject& world_object) {
  flecs::entity entity = it.entity(i);
  flecs::entity_t event = it.event();
  if (event == flecs::OnRemove) {
    entity.remove<SpatialInternal>();
  } else if (event == flecs::OnAdd) {
    const World* world_module = it.world().get<World>();
    if (!world_module) {
      ENGINE_ERROR("Cannot handle 'MonitorWorldObject' observer - failed to get 'World' - module");
      return;
    }

    auto [center, size] = calculate_bbox(world_object);
    std::unique_ptr<TreeObject> tree_object = world_module->get_space()->create_tree_object(entity, center, size);

    entity.emplace<SpatialInternal>(world_object, std::move(tree_object));
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

  world.observer<const world::WorldObject>("OnRemoveWorldObject")
    .event(flecs::Monitor)
    .each(MonitorWorldObject);

  world.observer("OnAddHandleIntersections")
    .event(flecs::OnAdd)
    .with<HandleIntersections>()
    .each(OnAddHandleIntersections);
}

} //end of engine::world
