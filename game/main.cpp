
#include <imgui.h>
#include <flecs.h>
#include <engine/lib/log.hpp>
#include <engine/lib/entry_consts.hpp>
#include <engine/world/world.hpp>
#include <engine/command.hpp>

#include "imgui-tools.hpp"

struct MyCommand {
  int hi = 123;
};

void engine_main(flecs::world & world) {
  world.set<flecs::Rest>({});
  world.import<flecs::monitor>();

  //init_imgui_tools(world);

  world.entity(engine::entry_consts::main_camera_name)
    .set<engine::world::Position>({.x=0, .y=0})
    .set<engine::world::Scale>({.x=1, .y=1})
    .add<engine::world::Rotation>();

/*
  world.entity("::test::drawable")
    .add<engine::world::WorldObject>()
    .add<engine::world::Renderable>()
    .set<engine::world::Color>(engine::world::color::gold)
    .set<engine::world::Position>({.x=0, .y=0})
    .set<engine::world::Scale>({.x=1.0f, .y=1.0f})
      //.set<engine::world::Rotation>({.angle=0.1f})
    ;
*/

  world.system("AutoExitSystem")
    .iter([](flecs::iter it) {
      static float close_after = 1;
      close_after -= it.delta_system_time();
      if (close_after <= 0.0f && !it.world().should_quit()) {
        //ENGINE_INFO("AUTOMATICAL EXIT");
        //it.world().quit();
      }
    });

  /*  auto kekus = world.entity("kekus");

    const flecs::entity_to_json_desc_t desc = {.serialize_path = false, .serialize_values = true};
    kekus.set<engine::world::Color>({.r = 1.0f, .g = 0.5f, .b = 0.1f});
    ENGINE_WARN("{}", kekus.to_json(&desc).c_str());

    const char* result = kekus.from_json(R"(
        {"ids":[["engine.world.Color"]], "values":[{"r":1, "g":0.5, "b":0.1000000015}]}
      )");
    ENGINE_INFO("from json result: {}", result ?: "nullptr");*/

  //-------------------------------------------------
  /*{
    using namespace engine::world;
    [[maybe_unused]] auto scope = world.scope(world.entity("test_scope"));

    auto parent = world.entity("parent")
      .add<WorldObject>()
      .add<Position>()
      .add<Scale>()
      .add<Rotation>();

    auto child = world.entity("child")
      .child_of(parent);

    world.entity("child_child")
      .add<WorldObject>()
      .add<Position>()
      .add<Scale>()
      .add<Rotation>()
      .child_of(child);
  }*/

  {
    using namespace engine::world;
    [[maybe_unused]] auto scope = world.scope(world.entity("test_intersections"));

    world.entity("object_1")
      .set<WorldObject>({.size_x = .5f, .size_y = .5f})
      .set<Scale>({.x = 2, .y = 2})
      .set<Position>({.x = 0.5f})
      .set<Color>(color::red)
      .add<HandleIntersections>()
      .add<Renderable>();

    world.entity("object_2")
      .add<WorldObject>()
      .add<Position>()
      //.add<HandleIntersections>()
      .add<Renderable>();
  }

}



