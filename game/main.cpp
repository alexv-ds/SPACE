
#include <imgui.h>
#include <flecs.h>
#include <engine/lib/log.hpp>
#include <engine/lib/entry_consts.hpp>
#include <engine/world/world.hpp>
#include <engine/command.hpp>

#include "imgui-tools.hpp"

void engine_main(flecs::world & world) {
  world.set<flecs::Rest>({});
  world.import<flecs::monitor>
  ();
  init_imgui_tools(world);

  world.entity(engine::entry_consts::main_camera_name)
    .set<engine::world::Position>({.x=0, .y=0})
    .set<engine::world::Scale>({.x=2, .y=2})
    .add<engine::world::Rotation>();

  world.entity("::test::drawable")
    .add<engine::world::WorldObject>()
    .add<engine::world::Renderable>()
    .set<engine::world::Color>(engine::world::color::gold)
    .set<engine::world::Position>({.x=0, .y=0})
    .set<engine::world::Scale>({.x=1.0f, .y=1.0f})
      //.set<engine::world::Rotation>({.angle=0.1f})
    .add<engine::world::IntersectsWith>(world.entity(engine::entry_consts::main_camera_name));

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

  {
    [[maybe_unused]] auto scope = world.scope(world.entity("commandtest"));

    /*auto prev_entity = flecs::entity::null();
    for (int i = 0; i < 10; ++i) {
      auto entity = world.entity((std::string("entity_") + std::to_string(i + 1)).c_str());
      if (prev_entity) {
        entity.add<engine::command::ConnectionNext>(prev_entity);
      }
      prev_entity = entity;
    }*/
  }

}



