#include <string>
#include "flecs_helpers.hpp"

namespace engine {

flecs::entity entity_by_stringview(flecs::world& world, const std::string_view& name) {
  static thread_local std::string name_buff;
  name_buff.clear();
  name_buff.append(name.begin(), name.end());
  return world.entity(name_buff.c_str());
}

}