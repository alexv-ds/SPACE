#include <flecs.h>
#include <engine/world/world.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

namespace engine::world {

void ApplyTransform(flecs::iter      it,
                    Transform*       transform_out,
                    const Position*  position,
                    const Rotation*  rotation,
                    const Scale*     scale)
{
  if (!it.changed()) {
    it.skip();
    return;
  }

  for (auto i : it) {
    transform_out[i].matrix = glm::mat3(1.0f);
  }

  if (position) {
    for (auto i : it) {
      transform_out[i].matrix = glm::translate(transform_out[i].matrix, glm::vec2(position[i].x, position[i].y));
    }
  }
  if (rotation) {
    for (auto i : it) {
      transform_out[i].matrix = glm::rotate(transform_out[i].matrix, rotation[i].angle);
    }
  }
  if (scale) {
    for (auto i : it) {
      transform_out[i].matrix = glm::scale(transform_out[i].matrix, glm::vec2(scale[i].x, scale[i].y));
    }
  }
}

void init_systems(flecs::world& world) {
  world.system<Transform, const Position, const Rotation, const Scale>("UpdateTransform")
    .kind(flecs::PostUpdate)
    .arg(3).optional()
    .arg(4).optional()
    .iter(ApplyTransform);
}

} //end of engine::world
