#pragma once
#include <flecs.h>

namespace engine {

struct World {
  explicit World(flecs::world&);
};

struct Reflection {
  explicit Reflection(flecs::world&);
};

} //end of namespace engine