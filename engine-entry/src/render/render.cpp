#include <engine/lib/log.hpp>
#include "render.hpp"

namespace engine::render_backend {

void init_phases(flecs::world&);
void init_observers(flecs::world&);
void init_components(flecs::world&);
void init_systems(flecs::world&);

} //end of namespace engine::render_backend

engine::RenderBackend::RenderBackend(flecs::world& world) {
  world.module<RenderBackend>("render_backend");
  render_backend::init_phases(world);
  render_backend::init_components(world);
  render_backend::init_observers(world);
  render_backend::init_systems(world);

  ENGINE_WARN("ХАЙ ДЮДЛС");
}