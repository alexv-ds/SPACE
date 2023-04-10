#pragma once
#include <flecs.h>
#include "../engine/TemlatedStringLiteral.hpp"
#include "../cvar.hpp"

#define ENGINE_CVAR_DEFINE(Type, Symbol, Name) using Symbol = ::engine::cvar::CvarStaticDefine<Type, Name>;

//using testcvar = ::engine::cvar::CvarStaticDefine<std::uint32_t, "testcvar">;

namespace engine::cvar {

template<class CvarType, TemlatedStringLiteral name>
struct CvarStaticDefine : noncopyable {
  inline static cvar_builder<CvarType> create(flecs::world& world, CvarType&& default_value) {
    return ::engine::cvar::create<CvarType>(world, name.value, std::move(default_value));
  }

  inline static void update(flecs::world& world, CvarType&& value) {
    ::engine::cvar::update<CvarType>(world, name.value, std::move(value));
  }

  inline static CvarType read(flecs::world& world) {
    return ::engine::cvar::read<CvarType>(world, name.value);
  }
};

} //namespace engine::cvar