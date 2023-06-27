#include "render.hpp"

namespace engine::render_backend {

void init_phases(flecs::world& world) {
  [[maybe_unused]] auto scope = world.scope(world.entity("phase"));

  world.component<PhaseBeginPre>()
    .add(flecs::Phase)
    .depends_on(flecs::OnStore);

  world.component<PhaseBegin>()
    .add(flecs::Phase)
    .depends_on<PhaseBeginPre>();

  world.component<PhaseStoreOrderedPre>()
    .add(flecs::Phase)
    .depends_on<PhaseBegin>();

  world.component<PhaseStoreOrdered>()
    .add(flecs::Phase)
    .depends_on<PhaseStoreOrderedPre>();

  world.component<PhaseCommitPre>()
    .add(flecs::Phase)
    .depends_on<PhaseStoreOrdered>();

  world.component<PhaseCommit>()
    .add(flecs::Phase)
    .depends_on<PhaseCommitPre>();
}

} //end of namespace engine::render_backend
