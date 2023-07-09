#pragma once
#include <flecs.h>

namespace engine::reflection {

struct ReflectedTypes {
  struct Glm {
    flecs::entity_t vec2 = flecs::entity::null();
    flecs::entity_t vec3 = flecs::entity::null();
    //flecs::entity_t mat3 = flecs::entity::null(); //TODO: assert при попытке посмотреть через wev панель
    flecs::entity_t mat2x3 = flecs::entity::null();
  };

  struct Std {
    flecs::entity_t string = flecs::entity::null();
  };

  Glm glm;
  Std std;
};

} //end of namespace engine::reflection