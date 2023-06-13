#include <stdexcept>
#include <atomic>
#include <sokol_app.h>
#include <sokol_gfx.h>
#include <sokol_glue.h>
#include <engine/log.hpp>
#include <engine/engine.hpp>
#include "sokol-gfx.hpp"

namespace engine::internal {


static std::atomic_flag g_gfx_initialised;

static void gfx_init(flecs::world& world) {
  SPDLOG_TRACE("on gfx init");
  if (g_gfx_initialised.test_and_set()) {
    throw std::logic_error("sokol gfx already initialised");
  }

  sg_setup({
    .logger = {
      .func = sokol_logfunc
    },
    .context = sapp_sgcontext()
  });
  world.add<SokolGfxContext>();
}

static void gfx_destroy(flecs::world& world) {
  ENGINE_TRACE("on gfx destroy");
  sg_shutdown();
  g_gfx_initialised.clear();
}

static void GfxInitSystem(flecs::iter it) {
  flecs::world world = it.world();
  gfx_init(world);
}


module::SokolGfx::SokolGfx(flecs::world& world) {
  world.module<SokolGfx>("::engine::internal::sokol_gfx");

  //components
  world.component<SokolGfxContext>();

  //systems
  world.system("system::GfxInitSystem")
    .with<SokolAppContext>().singleton()
    .without<SokolGfxContext>().singleton()
    .iter(GfxInitSystem);
  
  //observers
  {
    auto scope_guard = world.scope(world.entity("observer"));
    world.observer("OnDestroyAppContext")
      .event(flecs::OnRemove)
      .with<SokolAppContext>().singleton()
      .iter([](flecs::iter it) {
        flecs::world world = it.world();
        gfx_destroy(world);
      });
  }
}




};