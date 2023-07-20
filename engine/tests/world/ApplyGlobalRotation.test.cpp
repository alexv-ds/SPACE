#include <catch2/catch_test_macros.hpp>
#include <engine/engine.hpp>
#include <engine/world/transform.hpp>
#include "../helpers/helpers.hpp"

using namespace engine::world;

SCENARIO("ApplyGlobalRotation applies global rotation") {
  std::shared_ptr world = engine::create_world();
  test::disable_all(*world, {
    "::engine::world::system::ApplyGlobalRotation"
  });

  GIVEN("entity with Rotation and (Rotation, Global)") {
    flecs::entity e = world->entity();
    e.set<Rotation>({10});
    e.set<Rotation, Global>({0});

    WHEN("world run once") {
      engine::update_world(world);
      THEN("entity updates") {
        REQUIRE(e.has<Rotation, Global>());
        const auto* global_rotation = e.get<Rotation, Global>();
        REQUIRE(global_rotation->angle == 10);
      }
    }
  }

  GIVEN("entity with Rotation and (Rotation, Global) and parent") {
    flecs::entity parent = world->entity("parent")
      .set<Rotation>({3})
      .add<Rotation, Global>();

    flecs::entity child = world->entity("child")
      .set<Rotation>({10})
      .add<Rotation, Global>()
      .child_of(parent);

    WHEN("world run once") {
      engine::update_world(world);

      THEN("child (Rotation, Global) updates") {
        REQUIRE(child.has<Rotation, Global>());
        const auto* global_rotation = child.get<Rotation, Global>();
        REQUIRE(global_rotation->angle == 13);
      }
    }

    WHEN("world run 3 times") {
      for (auto i = 0; i < 5; ++i) {
        engine::update_world(world);
      }
      THEN("child (Rotation, Global) updates like run once") {
        REQUIRE(child.has<Rotation, Global>());
        const auto* global_rotation = child.get<Rotation, Global>();
        REQUIRE(global_rotation->angle == 13);
      }
    }
  }
}