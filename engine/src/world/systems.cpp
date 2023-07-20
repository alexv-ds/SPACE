#include <vector>
#include <set>
#include <flecs.h>
#include <engine/world/world.hpp>
#include <engine/lib/log.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include "../modules.hpp"

namespace engine::world {

static void UpdageWorldObject(flecs::iter it,
                              WorldObject* object,
                              const Position* position,
                              const Rotation* rotation,
                              const Scale* scale,
                              const WorldObject* parent)
{
  if (!it.changed()) {
    it.skip();
    return;
  }

  if (parent) {
    for (auto i : it) {
      object[i].global_position = parent[i].global_position;
      object[i].global_rotation = parent[i].global_rotation;
      object[i].global_scale = parent[i].global_scale;
    }
  } else {
    for (auto i : it) {
      object[i].global_position = {};
      object[i].global_rotation = {};
      object[i].global_scale = {};
    }
  }

  if (position) {
    for (auto i : it) {
      object[i].global_position.x += position[i].x;
      object[i].global_position.y += position[i].y;
    }
  }

  if (scale) {
    for (auto i : it) {
      object[i].global_scale.x *= scale[i].x;
      object[i].global_scale.y *= scale[i].y;
    }
  }

  if (rotation) {
    for (auto i : it) {
      object[i].global_rotation.angle += rotation[i].angle;
    }
  }
}

static void ApplyGlobalPosition(flecs::iter it,
                                const Position* local,
                                Position* global,
                                const Position* parent_global)
{
  if (!it.changed()) {
    it.skip();
    return;
  }

  if (parent_global) {
    for (auto i : it) {
      global[i] = parent_global[i];
      global[i].x += local[i].x;
      global[i].y += local[i].y;
    }
  } else {
    for (auto i : it) {
      global[i] = local[i];
    }
  }
}

void init_systems(flecs::world& world) {
  [[maybe_unused]] auto scope = world.scope(world.entity("system"));

  world.system<WorldObject, const Position, const Rotation, const Scale, const WorldObject>("UpdateWorldObject")
    .kind(flecs::PostUpdate)
    .arg(2).optional()
    .arg(3).optional()
    .arg(4).optional()
    .arg(5).cascade(flecs::ChildOf).optional()
    .iter(UpdageWorldObject);

  world.system<const Position, Position, const Position>("ApplyGlobalPosition")
    .kind(flecs::PostUpdate)
    .arg(2).second<Global>()
    .arg(3).cascade(flecs::ChildOf).optional().second<Global>()
    .iter(ApplyGlobalPosition);
}

} //end of engine::world
