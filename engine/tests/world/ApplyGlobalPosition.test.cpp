#include <catch2/catch_test_macros.hpp>
#include <engine/engine.hpp>
#include <engine/world/transform.hpp>
#include "../helpers/helpers.hpp"

using namespace engine::world;

SCENARIO("ApplyGlobalPosition applies global position") {
  std::shared_ptr world = engine::create_world();
  test::disable_all(*world, {
    "::engine::world::system::ApplyGlobalPosition"
  });

  GIVEN("entity with Position and (Position, Global)") {
    flecs::entity e = world->entity();
    e.set<Position>({.x = 10, .y = 20});
    e.set<Position, Global>({.x = 0, .y = 0});
    WHEN("world run once") {
      engine::update_world(world);
      THEN("(Position, Global) updates") {
        REQUIRE(e.has<Position, Global>());
        REQUIRE(e.has<Position>());
        const Position* gloval_pos = e.get<Position, Global>();
        REQUIRE(gloval_pos->x == 10);
        REQUIRE(gloval_pos->y == 20);
      }
    }
  }

  GIVEN("entity with Position and (Position, Global) and child") {
    flecs::entity parent = world->entity("parent")
      .set<Position>({.x = 5, .y = 0})
      .add<Position, Global>();

    flecs::entity child = world->entity("child")
      .set<Position>({.x = 5, .y = 1})
      .add<Position, Global>()
      .child_of(parent);

    WHEN("world run once") {
      engine::update_world(world);
      THEN("child (Position, Global) updates") {
        REQUIRE(child.has<Position, Global>());
        REQUIRE(child.has<Position>());
        const Position* gloval_pos = child.get<Position, Global>();
        REQUIRE(gloval_pos->x == 10);
        REQUIRE(gloval_pos->y == 1);
      }
    }

    WHEN("world run 5 times") {
      for (auto i = 0; i < 5; ++i) {
        engine::update_world(world);
      }

      THEN("child (Position, Global) updates like run once") {
        REQUIRE(child.has<Position, Global>());
        REQUIRE(child.has<Position>());
        const Position* gloval_pos = child.get<Position, Global>();
        REQUIRE(gloval_pos->x == 10);
        REQUIRE(gloval_pos->y == 1);
      }
    }
  }

  GIVEN("entity with Position, (Position, Global) and Disabled parent") {
    flecs::entity parent = world->entity("parent")
      .set<Position>({3,4})
      .add<Position, Global>()
      .add(flecs::Disabled);

    flecs::entity child = world->entity("child")
      .add<Position>()
      .add<Position, Global>()
      .child_of(parent);

    WHEN("world run once") {
      engine::update_world(world);
      THEN("child (Position, Global) not updates") {
        REQUIRE(child.has<Position, Global>());
        REQUIRE(child.has<Position>());
        const Position* gloval_pos = child.get<Position, Global>();
        REQUIRE(gloval_pos->x == 0);
        REQUIRE(gloval_pos->y == 0);
      }
    }

    WHEN("remove Disabled from parent and update world once") {
      parent.remove(flecs::Disabled);
      engine::update_world(world);
      THEN("child (Position, Global) updates") {
        REQUIRE(child.has<Position, Global>());
        REQUIRE(child.has<Position>());
        const Position* gloval_pos = child.get<Position, Global>();
        REQUIRE(gloval_pos->x == 3);
        REQUIRE(gloval_pos->y == 4);
      }
    }

  }

  GIVEN("entity with Position, (Position, Global) and empty parent component, but empty parent has parent "
        "with Position, (Position, Global)")
  {
    flecs::entity parent = world->entity("parent")
      .set<Position>({7,8})
      .add<Position, Global>();

    flecs::entity empty_parent = world->entity("empty_parent")
      .child_of(parent);

    flecs::entity child = world->entity("child")
      .set<Position>({1,1})
      .add<Position, Global>()
      .child_of(empty_parent);

    WHEN("world run once") {
      engine::update_world(world);
      THEN ("child updates") {
        REQUIRE(child.has<Position, Global>());
        REQUIRE(child.has<Position>());
        const Position* gloval_pos = child.get<Position, Global>();
        REQUIRE(gloval_pos->x == 8);
        REQUIRE(gloval_pos->y == 9);
      }
    }

    WHEN("empty_parent disabled and world run once") {
      empty_parent.add(flecs::Disabled);
      engine::update_world(world);

      THEN ("child not updates") {
        REQUIRE(child.has<Position, Global>());
        REQUIRE(child.has<Position>());
        const Position* child_global_pos = child.get<Position, Global>();
        REQUIRE(child_global_pos->x == 0);
        REQUIRE(child_global_pos->y == 0);
      }
    }
  }
}