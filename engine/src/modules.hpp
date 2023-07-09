#pragma once
#include <memory>
#include <flecs.h>
#include "world/spatial/SpatialSpace.hpp"

namespace engine {

struct World {
  explicit World(flecs::world&);

  inline const std::shared_ptr<world::SpatialSpace>& get_space() const {
    return this->space;
  }
private:
  std::shared_ptr<world::SpatialSpace> space;
};

struct Reflection {
  explicit Reflection(flecs::world&);
};

struct CommandModule {
  explicit CommandModule(flecs::world&);
};

} //end of namespace engine