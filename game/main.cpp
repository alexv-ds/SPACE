#include <cmath>
#include <random>
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

std::random_device g_random_device;
std::mt19937 g_gen(g_random_device());
std::uniform_real_distribution<float> g_distribution(-1.0f, 1.0f);

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
        ENGINE_INFO("AUTOMATICAL EXIT");
        it.world().quit();
      }
    })
    .add(flecs::Disabled);

  {
    using namespace engine::world;
    [[maybe_unused]] auto scope = world.scope(world.entity("test_intersections"));

    std::random_device random_device;
    std::mt19937 gen(random_device());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    struct BasePosition {
      float x = 0.0f;
      float y = 0.0f;
    };

    for (int x = -1; x <= 1; ++x) {
      for (int y = -1; y <= 1; ++y) {
        world.entity()
          .set<WorldObject>({.size_x = 1, .size_y = 1})
          .set<Position>({.x = (float)x, .y = (float)y})
          .set<BasePosition>({.x = (float)x, .y = (float)y})
          .add<HandleIntersections>()
          .add<Renderable>()
          .add<IntersectsWith>(world.entity(engine::entry_consts::main_camera_name))
          .set<Color>({
            .r = dis(gen),
            .g = dis(gen),
            .b = dis(gen)
          });
      }
    }



    world.system<Position, const BasePosition>("position_changer")
      .each([](flecs::entity e, Position& pos, const BasePosition& base_pos) {
        pos.x = base_pos.x + g_distribution(g_gen);
        pos.y = base_pos.y + g_distribution(g_gen);
      })
      .add(flecs::Disabled)
      ;

    world.entity(engine::entry_consts::main_camera_name).set<Scale>({.x = 10, .y = 10});

  }

}



