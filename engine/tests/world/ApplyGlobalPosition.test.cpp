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
        const auto* gloval_pos = e.get<Position, Global>();
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
        const auto* gloval_pos = child.get<Position, Global>();
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
        const auto* gloval_pos = child.get<Position, Global>();
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
      .set<Position>({1,1})
      .add<Position, Global>()
      .child_of(parent);

    WHEN("world run once") {
      engine::update_world(world);
      THEN("child (Position, Global) updates without parent") {
        REQUIRE(child.has<Position, Global>());
        REQUIRE(child.has<Position>());
        const auto* gloval_pos = child.get<Position, Global>();
        REQUIRE(gloval_pos->x == 1);
        REQUIRE(gloval_pos->y == 1);
      }
    }

    WHEN("remove Disabled from parent and update world once") {
      parent.remove(flecs::Disabled);
      engine::update_world(world);
      THEN("child (Position, Global) updates") {
        REQUIRE(child.has<Position, Global>());
        REQUIRE(child.has<Position>());
        const auto* gloval_pos = child.get<Position, Global>();
        REQUIRE(gloval_pos->x == 4);
        REQUIRE(gloval_pos->y == 5);
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
        const auto* gloval_pos = child.get<Position, Global>();
        REQUIRE(gloval_pos->x == 8);
        REQUIRE(gloval_pos->y == 9);
      }
    }

    WHEN("empty_parent disabled and world run once") {
      empty_parent.add(flecs::Disabled);
      engine::update_world(world);

      THEN ("child updates") {
        REQUIRE(child.has<Position, Global>());
        REQUIRE(child.has<Position>());
        const auto* child_global_pos = child.get<Position, Global>();
        REQUIRE(child_global_pos->x == 8);
        REQUIRE(child_global_pos->y == 9);
      }
    }
  }

  GIVEN("entity with Position, (Position, Global) and parent_head, parent_middle") {
    auto parent_top = world->entity()
      .set<Position>({1,1})
      .add<Position, Global>();

    auto parent_middle = world->entity()
      .set<Position>({2,2})
      .add<Position, Global>()
      .child_of(parent_top);

    auto child = world->entity()
      .set<Position>({3,3})
      .add<Position, Global>()
      .child_of(parent_middle);

    WHEN("world run once") {
      engine::update_world(world);

      THEN("child and middle_parent updates") {
        REQUIRE(parent_middle.has<Position, Global>());
        REQUIRE(child.has<Position, Global>());
        const auto* parent_middle_global_position = parent_middle.get<Position, Global>();
        const auto* child_global_position = child.get<Position, Global>();

        REQUIRE(parent_middle_global_position->x == 3);
        REQUIRE(parent_middle_global_position->y == 3);
        REQUIRE(child_global_position->x == 6);
        REQUIRE(child_global_position->y == 6);
      }
    }
    WHEN("top disabled and world run once") {
      parent_top.add(flecs::Disabled);
      engine::update_world(world);
      THEN("middle and child updates without top") {
        REQUIRE(parent_middle.has<Position, Global>());
        REQUIRE(child.has<Position, Global>());
        const auto* parent_middle_global_position = parent_middle.get<Position, Global>();
        const auto* child_global_position = child.get<Position, Global>();

        REQUIRE(parent_middle_global_position->x == 2);
        REQUIRE(parent_middle_global_position->y == 2);
        REQUIRE(child_global_position->x == 5);
        REQUIRE(child_global_position->y == 5);
      }
    }
    WHEN("middle disabled and world run once") {
      parent_middle.add(flecs::Disabled);
      engine::update_world(world);
      THEN("child updates without top and middle") {
        REQUIRE(child.has<Position, Global>());
        const auto* child_global_position = child.get<Position, Global>();
        REQUIRE(child_global_position->x == 3); //OK
        REQUIRE(child_global_position->y == 3); //OK
      }
    }
  }
}