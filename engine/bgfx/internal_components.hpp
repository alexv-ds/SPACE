#pragma once
#include <flecs.h>
#include <cstdint>

namespace engine::bgfx::detail {

void register_internal_components(flecs::world&);

struct UpdateResetFlags {};
struct ResetFlags {
  std::uint32_t flags;
};
struct UpdateDebugFlags {};
struct UpdateClearData {};

} //namespace engine::bgfx::detail