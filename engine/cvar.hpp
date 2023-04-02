#pragma once
#include <functional>
#include <cstdint>
#include <flecs.h>
#include "cvar/internal.hpp"

/*
  Supported Vars

  int32_t
  uint32_t
  int64_t
  uint64_t
  bool
  float
  string
*/

namespace engine::cvar {
  template <class T>
  using ChangeCb = std::function<void(flecs::entity, const T&)>;

  template <class T>
  void register_type(flecs::world& world, const char* const type_name) {
    flecs::entity data_component = world.component<internal::CVarDataTypeWrapper<T>>(type_name);

    world.component<internal::CVarUpdateCallback<T>>("update_callback")
      .child_of(data_component);
  }

  template <class T>
  void create(flecs::world& world, const char* const name, T&& default_value) {
    using ComponentType = internal::CVarDataTypeWrapper<T>;
    flecs::entity cvar = world.entity(name);
    cvar.set<ComponentType, internal::DataDefault>({.value = std::move(default_value)});
    cvar.set<ComponentType, internal::DataCurrent>({.value = std::move(default_value)});
    cvar.add<internal::NotifyCallbacks>();
      //.set<ComponentType, internal::DataDefault>({.value = std::move(default_value)});
  }

  template <class T>
  void update(flecs::world& world, const char* const name, T&& value);

  template <class T>
  void change_callback(flecs::world& world, const char* const name, ChangeCb<T>&& cb);
}
