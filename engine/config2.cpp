#include <spdlog/spdlog.h>
#include "config2.hpp"

namespace engine::config2 {

  namespace detail {


  };

} //namespace engine::config2

engine::Config2::Config2(flecs::world& world) {
  using namespace config2;
  world.module<Config2>("config2");

 world.component<ValidatedData>();
 world.component<UnValidatedData>();
 world.component<DefaultData>();
 world.component<Validator>();
 world.component<ConfigVar>()
  .member(flecs::Entity, "data_component");
  world.component<type::Int32>("Int32")
    .member<decltype(type::Int32::value)>("value");
  world.component<type::Uint32>("Uint32")
    .member<decltype(type::Uint32::value)>("value");

  
  //world.system<>()

};
