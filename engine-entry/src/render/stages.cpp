#include "render.hpp"

namespace engine::render_backend {

void init_phases(flecs::world& world) {
  [[maybe_unused]] auto scope = world.scope(world.entity("phase"));

  world.component<PhaseRenderBeginPre>()
    .add(flecs::Phase)
    .depends_on(flecs::OnStore);

  world.component<PhaseRenderBegin>()
    .add(flecs::Phase)
    .depends_on<PhaseRenderBeginPre>();

  world.component<PhaseRenderOrderedPre>()
    .add(flecs::Phase)
    .depends_on<PhaseRenderBegin>();

  world.component<PhaseRenderOrdered>()
    .add(flecs::Phase)
    .depends_on<PhaseRenderOrderedPre>();

  world.component<PhaseCommitPre>()
    .add(flecs::Phase)
    .depends_on<PhaseRenderOrdered>();

  world.component<PhaseCommit>()
    .add(flecs::Phase)
    .depends_on<PhaseCommitPre>();
}

} //end of namespace engine::render_backend
