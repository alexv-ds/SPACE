#pragma once
#include <flecs.h>

namespace engine {

//supports
/*
  glm::vec2
  glm::vec3
  glm::mat3
*/

struct GlmReflection {
  GlmReflection(flecs::world&);
};

}
