#include <flecs.h>
#include <engine/lib/assert.hpp>
#include <engine/reflection.hpp>
#include <engine/world/world.hpp>
#include <engine/world/transform.hpp>
#include <engine/world/spatial.hpp>
#include <engine/world/graphics.hpp>

namespace engine::world {

void init_components(flecs::world& world) {
  const auto* reflected = world.get<reflection::ReflectedTypes>();
  ENGINE_ASSERT(reflected != nullptr);


  world.component<Scale>()
    .member<decltype(Scale::x)>("x")
    .member<decltype(Scale::y)>("y");

  world.component<Rotation>()
    .member<decltype(Rotation::angle), flecs::units::angle::Radians>("angle");

  world.component<Position>()
    .member<decltype(Position::x)>("x")
    .member<decltype(Position::y)>("y");

  world.component<WorldObject>()
    .member<decltype(WorldObject::size_x)>("size_x")
    .member<decltype(WorldObject::size_y)>("size_y")
    .member<decltype(WorldObject::global_position)>("global_position")
    .member<decltype(WorldObject::global_scale)>("global_scale")
    .member<decltype(WorldObject::global_rotation)>("global_rotation");

  world.component<Transform>();

  world.component<HandleIntersections>();
  world.component<InitIntersections>();
  world.component<IntersectsWith>()
    .add(flecs::Symmetric);

  world.component<Renderable>();
  world.component<Icon>()
    .member(reflected->std.string,"icon")
    .member(reflected->std.string,"icon_state");

  world.component<Layer>()
    .member<decltype(Layer::layer)>("layer");

  world.component<Color>()
    .member<decltype(Color::r)>("r")
    .member<decltype(Color::g)>("g")
    .member<decltype(Color::b)>("b");

  world.component<Transparency>()
    .member<decltype(Transparency::alpha)>("alpha");

  world.component<Global>();
}

} //end of namespace engine::world


