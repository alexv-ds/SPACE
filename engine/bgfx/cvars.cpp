#pragma once
#include <flecs.h>
#include "../config.hpp"
#include "cvars.hpp"
#include "internal_components.hpp"

#include <spdlog/spdlog.h>

namespace engine::bgfx::detail {

static void reset_flags_mark_to_update(flecs::world& world, const config::VariantType&) {
  world.add<UpdateResetFlags>();
}

static void update_debug_flags(flecs::world& world, const config::VariantType&) {
  world.add<UpdateDebugFlags>();
}

//defined in engine/bgfx.cpp
void register_cvars(flecs::world& world) {
  config::create_var(world, cvar::capture, 0);
  config::create_var(world, cvar::flush_after_render, 0);
  config::create_var(world, cvar::maxanisotropy, 0);
  config::create_var(world, cvar::vsync, 0);
  config::create_var_listener(world, cvar::capture, reset_flags_mark_to_update);
  config::create_var_listener(world, cvar::flush_after_render, reset_flags_mark_to_update);
  config::create_var_listener(world, cvar::maxanisotropy, reset_flags_mark_to_update);
  config::create_var_listener(world, cvar::vsync, reset_flags_mark_to_update);

  config::create_var(world, cvar::debug_ihf, 0);
  config::create_var(world, cvar::debug_profiler, 0);
  config::create_var(world, cvar::debug_stats, 0);
  config::create_var(world, cvar::debug_text, 0);
  config::create_var(world, cvar::debug_wireframe, 0);
  config::create_var_listener(world, cvar::debug_ihf, update_debug_flags);
  config::create_var_listener(world, cvar::debug_profiler, update_debug_flags);
  config::create_var_listener(world, cvar::debug_stats, update_debug_flags);
  config::create_var_listener(world, cvar::debug_text, update_debug_flags);
  config::create_var_listener(world, cvar::debug_wireframe, update_debug_flags);  
} 



} //namespace engine::bgfx::detail