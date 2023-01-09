#include "glm-reflection.hpp"
#include <glm/vec2.hpp>
#include <glm/mat2x3.hpp>

namespace engine {

GlmReflection::GlmReflection(flecs::world& world) {
  world.module<GlmReflection>("glm_reflection");
  
  static_assert(sizeof(glm::vec2) == sizeof(float) * 2);
  world.component<glm::vec2>("vec2")
    .member<float>("x")
    .member<float>("y");
}

} //namespace engine
