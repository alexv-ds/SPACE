#pragma once
#include <memory>
#include <flecs.h>

namespace engine {

struct World {
  explicit World(flecs::world&);
};

struct Reflection {
  explicit Reflection(flecs::world&);
};

struct CommandModule {
  explicit CommandModule(flecs::world&);
};

} //end of namespace engine