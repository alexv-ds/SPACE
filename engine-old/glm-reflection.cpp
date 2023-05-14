#include <type_traits>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include "glm-reflection.hpp"

namespace engine {

GlmReflection::GlmReflection(flecs::world& world) {
  world.module<GlmReflection>("glm_reflection");
  
  static_assert(sizeof(glm::vec2) == sizeof(float) * 2);
  world.component<glm::vec2>("glm_vec2")
    .member<float>("x")
    .member<float>("y");

  static_assert(sizeof(glm::vec3) == sizeof(float) * 3);
  world.component<glm::vec3>("glm_vec3")
    .member<float>("x")
    .member<float>("y")
    .member<float>("z");
  
  static_assert(std::is_same_v<glm::mat3::col_type, glm::vec3>);
  static_assert(std::is_same_v<glm::mat3::row_type, glm::vec3>);
  world.component<glm::mat3>("glm_mat3")
    .member<glm::vec3>("col1")
    .member<glm::vec3>("col2")
    .member<glm::vec3>("col3");
}

} //namespace engine
