#pragma once
#include <functional>
#include <cstdint>
#include <flecs.h>

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

namespace cvar {
  template <class T>
  using ChangeCb = std::function<void(flecs::entity, const T&);

  template <class T>
  void register_type(flecs::world& world, const char* const type_name);

  template <class T>
  void create(flecs::world& world, const char* const name, T&& default_value);

  template <class T>
  void update(flecs::world& world, const char* const name, T&& value);

  template <class T>
  void change_callback(flecs::world& world, const char* const name);



}