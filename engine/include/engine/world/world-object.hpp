#pragma once
#include <string>
#include <cstdint>
#include "flecs.h"

namespace engine::world {

struct WorldObject {
  float size_x = 1.0f;
  float size_y = 1.0f;
};

} //end of namespace engine