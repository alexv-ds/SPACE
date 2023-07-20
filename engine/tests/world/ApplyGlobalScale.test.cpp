#include <catch2/catch_test_macros.hpp>
#include <engine/engine.hpp>
#include <engine/world/transform.hpp>
#include "../helpers/helpers.hpp"

using namespace engine::world;

SCENARIO("ApplyGlobalScale applies global scale") {
  std::shared_ptr world = engine::create_world();
  test::disable_all(*world, {
    "::engine::world::system::ApplyGlobalScale"
  });

  GIVEN("entity with Scale and (Scale, Global)") {
    flecs::entity e = world->entity();
    e.set<Scale>({.x = 3, .y = 4});
    e.set<Scale, Global>({.x = 0, .y = 0});

    WHEN("world run once") {
      engine::update_world(world);
      engine::update_world(world);
      engine::update_world(world);
      engine::update_world(world);
      engine::update_world(world);
      engine::update_world(world);
      engine::update_world(world);

      THEN("entity updates") {
        REQUIRE(e.has<Scale, Global>());
        const auto* global_scale = e.get<Scale, Global>();
        REQUIRE(global_scale->x == 3);
        REQUIRE(global_scale->y == 4);
      }
    }
  }

  GIVEN("entity with Scale and (Scale, Global) and parent") {
    flecs::entity parent = world->entity("parent")
      .set<Scale>({.x = 1, .y = 2})
      .add<Scale, Global>();

    flecs::entity child = world->entity("child")
      .set<Scale>({.x = 2, .y = 2})
      .add<Scale, Global>()
      .child_of(parent);

    WHEN("world run once") {
      engine::update_world(world);

      THEN("child (Scale, Global) updates") {
        REQUIRE(child.has<Scale, Global>());
        const auto* global_scale = child.get<Scale, Global>();
        REQUIRE(global_scale->x == 2);
        REQUIRE(global_scale->y == 4);
      }

    }

    WHEN("world run 3 times") {
      for (auto i = 0; i < 5; ++i) {
        engine::update_world(world);
      }
      THEN("child (Scale, Global) updates like run once") {
        REQUIRE(child.has<Scale, Global>());
        const auto* global_scale = child.get<Scale, Global>();
        REQUIRE(global_scale->x == 2);
        REQUIRE(global_scale->y == 4);
      }
    }
  }
}