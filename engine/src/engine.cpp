#include <engine/engine.hpp>
#include "debug.hpp"
#include "internal-modules/sokol-gfx.hpp"
#include "graphics.hpp"

namespace engine {

static void import_core(flecs::world& world) {
  [[maybe_unused]] auto scope_guard = world.scope(
    world.entity("engine").add(flecs::Module)
  );

  world.component<SokolAppContext>();
  world.component<SokolGfxContext>();

  world.import<internal::module::SokolGfx>();
  world.import<Graphics>();
}

std::shared_ptr<flecs::world> create_world(int argc, char* argv[]) {
  return create_world();
}

std::shared_ptr<flecs::world> create_world() {
  std::shared_ptr world = std::make_shared<flecs::world>();
  world->set_threads(2);

  import_core(*world);

  world->import<Debug>();
  return world;
}

bool update_world(flecs::world& world, const float dt) {
  return world.progress();
}

  
} //namespace engine

