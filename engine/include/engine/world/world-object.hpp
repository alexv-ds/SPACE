#pragma once
#include <string>
#include <cstdint>
#include "flecs.h"
#include "transform.hpp"

namespace engine::world {

struct WorldObject {
  float size_x = 1.0f;
  float size_y = 1.0f;

  //global position
  Position global_position;
  Scale global_scale;
  Rotation global_rotation;

  inline bool operator==(const WorldObject& other) const {
    return
      other.global_position.x == this->global_position.x
        && other.global_position.y == this->global_position.y
        && other.global_scale.x == this->global_scale.x
        && other.global_scale.y == this->global_scale.y
        && other.global_rotation.angle == this->global_rotation.angle;
  }
};

} //end of namespace engine