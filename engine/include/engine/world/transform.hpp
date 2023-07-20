#pragma once
#include <glm/mat3x3.hpp>

namespace engine::world {

struct Scale {
  float x = 1.0f;
  float y = 1.0f;
};

struct Rotation {
  float angle = 0.0f; //radians
};

struct Position {
  float x = 0.0f;
  float y = 0.0f;
};

struct Transform {
  glm::mat3 matrix = glm::mat3(1.0f);
};

struct Global {};

} //end of namespace engine::world