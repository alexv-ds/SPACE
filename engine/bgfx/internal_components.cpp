#include <type_traits>
#include <bgfx/bgfx.h>
#include "internal_components.hpp"

namespace engine::bgfx::detail {

void register_internal_components(flecs::world& world) {
  world.component<UpdateResetFlags>("detail::UpdateResetFlags");

  static_assert(std::is_same_v<decltype(ResetFlags::flags), decltype(::bgfx::Resolution::reset)>);
  world.component<ResetFlags>("detail::ResetFlags");
  world.add<ResetFlags>();

  world.component<UpdateDebugFlags>();
}


} //namespace engine::bgfx::detail