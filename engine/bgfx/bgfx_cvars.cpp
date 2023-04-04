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
  ::engine::cvar::create<bool>(world, cvar::capture, false)
    .on_change(reset_flags_mark_to_update);
  ::engine::cvar::create<bool>(world, cvar::flush_after_render, false)
    .on_change(reset_flags_mark_to_update);
  ::engine::cvar::create<bool>(world, cvar::maxanisotropy, false)
    .on_change(reset_flags_mark_to_update);
  ::engine::cvar::create<bool>(world, cvar::vsync, false)
    .on_change(reset_flags_mark_to_update);

  ::engine::cvar::create<bool>(world, cvar::debug_ihf, false)
    .on_change(update_debug_flags);
  ::engine::cvar::create<bool>(world, cvar::debug_profiler, false)
    .on_change(update_debug_flags);
  ::engine::cvar::create<bool>(world, cvar::debug_stats, false)
    .on_change(update_debug_flags);
  ::engine::cvar::create<bool>(world, cvar::debug_text, false)
    .on_change(update_debug_flags);
  ::engine::cvar::create<bool>(world, cvar::debug_wireframe, false)
    .on_change(update_debug_flags);

  ::engine::cvar::create<bool>(world, cvar::mainwindow_clear_depth, false)
    .on_change(update_clear_data<bool>);
  ::engine::cvar::create<bool>(world, cvar::mainwindow_clear_stencil, false)
    .on_change(update_clear_data<bool>);
  ::engine::cvar::create<std::uint32_t>(world, cvar::mainwindow_clear_color_value, 0x000000ff)
    .on_change(update_clear_data<std::uint32_t>);
  ::engine::cvar::create<float>(world, cvar::mainwindow_clear_depth_value, 0.0f)
    .on_change(update_clear_data<float>);
  ::engine::cvar::create<std::uint8_t>(world, cvar::mainwindow_clear_stencil_value, 0)
    .on_change(update_clear_data<std::uint8_t>);
} 



} //namespace engine::bgfx::detail