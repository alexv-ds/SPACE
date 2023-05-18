#include "cvar.hpp"
#include <string>
#include <cstdint>

namespace engine {

Cvar::Cvar(flecs::world& world) {
  using namespace cvar;
  world.module<Cvar>("cvar");

  world.component<internal::DataCurrent>("internal::DataCurrent");
  world.component<internal::DataDefault>("internal::DataDefault");

  register_type<std::string>(world, "string");
  register_type<std::int8_t>(world, "int8");
  register_type<std::uint8_t>(world, "uint8");
  register_type<std::int32_t>(world, "int32");
  register_type<std::uint32_t>(world, "uint32");
  register_type<std::int64_t>(world, "int64");
  register_type<std::uint64_t>(world, "uint64");
  register_type<bool>(world, "bool");
  register_type<float>(world, "float");
}

} //namespace engine