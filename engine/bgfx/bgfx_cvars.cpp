#include <flecs.h>
#include "../cvar.hpp"
#include "bgfx_cvars.hpp"
#include "internal_components.hpp"

namespace engine::bgfx::detail {

static void reset_flags_mark_to_update(flecs::entity e, const bool&) {
  e.world().add<UpdateResetFlags>();
}

static void update_debug_flags(flecs::entity e, const bool&) {
  e.world().add<UpdateDebugFlags>();
}

template<class CvarType>
static void update_clear_data(flecs::entity e, const CvarType&) {
  e.world().add<UpdateClearData>();
}

//function defined and used in engine/bgfx.cpp
void register_cvars(flecs::world& world) {
  cvar::capture::create(world, false)           .on_change(reset_flags_mark_to_update);
  cvar::flush_after_render::create(world, false).on_change(reset_flags_mark_to_update);
  cvar::maxanisotropy::create(world, false)     .on_change(reset_flags_mark_to_update);
  cvar::vsync::create(world, false)             .on_change(reset_flags_mark_to_update);

  cvar::debug_ihf::create(world, false)      .on_change(update_debug_flags);
  cvar::debug_profiler::create(world, false) .on_change(update_debug_flags);
  cvar::debug_stats::create(world, false)    .on_change(update_debug_flags);
  cvar::debug_text::create(world, false)     .on_change(update_debug_flags);
  cvar::debug_wireframe::create(world, false).on_change(update_debug_flags);

  cvar::mainwindow_clear_depth::create(world, false)           .on_change(update_clear_data<bool>);
  cvar::mainwindow_clear_stencil::create(world, false)         .on_change(update_clear_data<bool>);
  cvar::mainwindow_clear_color_value::create(world, 0x000000ff).on_change(update_clear_data<std::uint32_t>);
  cvar::mainwindow_clear_depth_value::create(world, 0.0f)      .on_change(update_clear_data<float>);
  cvar::mainwindow_clear_stencil_value::create(world, 0)       .on_change(update_clear_data<std::uint8_t>);

  cvar::render_backend::create(world, "vulkan");
} 



} //namespace engine::bgfx::detail