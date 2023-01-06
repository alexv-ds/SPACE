#include "transform.hpp"

namespace engine {

Transform::Transform(flecs::world& world) {
  world.module<Transform>("transform");
}

} //namespace engine