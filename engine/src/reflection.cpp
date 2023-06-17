#include <type_traits>
#include <string>
#include <flecs.h>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat2x3.hpp>
#include <engine/reflection.hpp>
#include "modules.hpp"

namespace engine {

Reflection::Reflection(flecs::world& world) {
  world.module<Reflection>("reflection");

  static_assert(sizeof(glm::vec2) == sizeof(float) * 2);
  static_assert(std::is_same_v<glm::vec2::value_type, float>);
  world.component<glm::vec2>("glm::vec2")
    .member<float>("x")
    .member<float>("y");

  static_assert(sizeof(glm::vec3) == sizeof(float) * 3);
  static_assert(std::is_same_v<glm::vec3::value_type, float>);
  world.component<glm::vec3>("glm::vec3")
    .member<float>("x")
    .member<float>("y")
    .member<float>("z");

  static_assert(std::is_same_v<glm::mat3::col_type, glm::vec3>);
  static_assert(std::is_same_v<glm::mat3::row_type, glm::vec3>);
  static_assert(sizeof(glm::mat3) == sizeof(float) * 3 * 3);
  world.component<glm::mat3>("glm::mat3")
    .member<glm::vec3>("col1")
    .member<glm::vec3>("col2")
    .member<glm::vec3>("col3");

  static_assert(std::is_same_v<glm::mat2x3::col_type, glm::vec3>);
  static_assert(std::is_same_v<glm::mat2x3::row_type, glm::vec2>);
  static_assert(sizeof(glm::mat2x3) == sizeof(float) * 3 * 2);
  world.component<glm::mat2x3>("glm::mat2x3")
    .member<glm::vec2>("col1")
    .member<glm::vec2>("col2")
    .member<glm::vec2>("col3");

  world.component<std::string>("std::string")
    .opaque(flecs::String) // Opaque type that maps to string
    .serialize([](const flecs::serializer *s, const std::string *data) {
      const char *str = data->c_str();
      return s->value(flecs::String, &str); // Forward to serializer
    })
    .assign_string([](std::string* data, const char *value) {
      *data = value; // Assign new value to std::string
    });

  world.component<reflection::ReflectedTypes>();
  world.set<reflection::ReflectedTypes>({
    .glm = {
      .vec2 = world.entity<glm::vec2>(),
      .vec3 = world.entity<glm::vec3>(),
      .mat3 = world.entity<glm::mat3>(),
      .mat2x3 = world.entity<glm::mat2x3>()
    },
    .std = {
      .string = world.entity<std::string>()
    }
  });


}

}