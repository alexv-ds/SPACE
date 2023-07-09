#include <vector>
#include <set>
#include <flecs.h>
#include <engine/world/world.hpp>
#include <engine/lib/log.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include "spatial/component.hpp"

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

static void UpdateSpatial(flecs::iter it,
                          const WorldObject* object,
                          SpatialInternal* spatial_internal,
                          const InitIntersections* init_intersections)
{
  for (auto i : it) {
    const bool has_changes = spatial_internal[i].update(object[i]);
    if (has_changes || init_intersections) {
      ENGINE_DEBUG("HI DUDDLE");
      flecs::entity entity = it.entity(i);
      if (init_intersections) {
        entity.remove<InitIntersections>();
      }

      static thread_local std::vector<flecs::entity_t> intersections;
      static thread_local std::set<flecs::entity_t> current_intersections;
      intersections.clear();
      current_intersections.clear();

      //fill current_intersections set
      entity.each<IntersectsWith>([](flecs::id id) {
        current_intersections.insert(id.second());
      });

      //fill intersections vector
      spatial_internal->get_tree_object().query_intersects(intersections);

      //update relations
      for (flecs::entity_t intersected_entity : intersections) {
        //если не удалось убрать элемент из списка текущих пересечений
        //значит это НОВОЕ пересечение, добавляем его
        if (!current_intersections.erase(intersected_entity)) {
          entity.add<IntersectsWith>(intersected_entity);
        }


      }
      //в этой точке в списке current_intersections остались сущности
      //с которыми больше не пересекается объект, удаляем их с него
      for (flecs::entity_t no_intersected_entity : current_intersections) {
        entity.remove<IntersectsWith>(no_intersected_entity);
        ENGINE_WARN(no_intersected_entity);
      }

      //очищаем массивы (опять, лишним вообще не будет)
      intersections.clear();
      current_intersections.clear();
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

  world.system<const WorldObject, SpatialInternal, const InitIntersections>("UpdateSpatial")
    .kind(flecs::PostUpdate)
    .arg(3).optional()
    .iter(UpdateSpatial);
}

} //end of engine::world
