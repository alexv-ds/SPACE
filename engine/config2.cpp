#include <spdlog/spdlog.h>
#include "config2.hpp"

namespace engine::config2 {

  namespace detail {


  };

  template <class T>
  flecs::entity create_var(flecs::world& world, const char* name, T&& data) {
    flecs::entity entity = world.entity(name);
    return entity;
  }

  template flecs::entity create_var<type::Int32>(flecs::world& world, const char* name, type::Int32&& data);


} //namespace engine::config2

engine::Config2::Config2(flecs::world& world) {
  using namespace config2;
  world.module<Config2>("config2");

  world.component<type::Int32>("Int32")
    .member<decltype(type::Int32::value)>("value");


};
