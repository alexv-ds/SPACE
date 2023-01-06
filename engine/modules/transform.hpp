#pragma once
#include <flecs.h>
#include <glm/mat3x3.hpp>

namespace engine {

struct Transform {
  Transform(flecs::world&);
};

} //namespace engine

namespace engine::transform {

struct Position2 {
  float x;
  float y;
};

struct Scale2 {
  float x;
  float y;
};

struct Rotation2 {
  float angle; //in radians
};

struct Transform2 {
  glm::mat3 value;
};

} //namespace engine::transform