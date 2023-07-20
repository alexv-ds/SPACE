#include <random>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_get_random_seed.hpp>
#include <engine/engine.hpp>
#include <engine/world/transform.hpp>
#include "../helpers/helpers.hpp"

using namespace engine::world;

void build_chain(flecs::entity e, int wide, int depth) {
  for (auto i = 0; i < wide; ++i) {
    auto new_entity = e.world().entity()
      .add<Position>()
      .child_of(e);
    if (depth > 0) {
      build_chain(new_entity, wide, depth-1);
    }
  }
}

SCENARIO("When adding Position on entity then initialised (Position, Global)") {
  std::shared_ptr world = engine::create_world();
  test::disable_all(*world, {
    "::engine::world::observer::MonitorPosition"
  });

  GIVEN("entitiy with Position and without (Position, Global) and has parent") {

    flecs::entity parent = world->entity()
      .add<Position>()
      .add<Position, Global>();

    flecs::entity child = world->entity()
      .add<Position>()
      .child_of(parent);

    WHEN("world run once") {
      engine::update_world(world);
      THEN("(Position, Global) initialised") {
        REQUIRE(child.has<Position, Global>());
      }
    }
  }

  GIVEN("some entities with childs") {
    build_chain(world->entity(), 2, 10);
    build_chain(world->entity(), 1, 10);
    build_chain(world->entity(), 1, 10);

    WHEN("world destroy") {
      THEN("Has no assert") {
        world = nullptr;
      }
    }
  }

}