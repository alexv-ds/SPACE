
#include <imgui.h>
#include <flecs.h>
#include <engine/lib/log.hpp>
#include <engine/world/world.hpp>

const char* const g_main_camera_name = "::engine::entry::main_camera";


void engine_main(flecs::world& world) {
  world.set<flecs::Rest>({});
  world.import<flecs::monitor>();

  world.entity("::engine::entry::main_camera")
    .set<engine::world::Position>({.x=0, .y=0})
    .set<engine::world::Scale>({.x=4, .y=4});

  world.entity("::test::drawable")
    .add<engine::world::WorldObject>()
    .add<engine::world::Renderable>()
    .set<engine::world::Color>(engine::world::color::red)
    .set<engine::world::Position>({.x=0, .y=0})
    .add<engine::world::IntersectsWith>(world.entity(g_main_camera_name));




}

