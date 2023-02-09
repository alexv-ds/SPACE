#include "config2.hpp"

namespace engine::config2 {

  template <class T>
  void create_var(flecs::world& world, const char* name, T&& data) {}

  template void create_var<type::Int32>(flecs::world& world, const char* name, type::Int32&& data);


} //namespace engine::config2