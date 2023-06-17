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

  world.component<WorldObject>()
    .member<decltype(WorldObject::size_x)>("size_x")
    .member<decltype(WorldObject::size_y)>("size_y");

  world.component<Scale>()
    .member<decltype(Scale::x)>("x")
    .member<decltype(Scale::y)>("y");

  world.component<Rotation>()
    .member<decltype(Rotation::angle), flecs::units::angle::Radians>("angle");

  world.component<Position>()
    .member<decltype(Position::x)>("x")
    .member<decltype(Position::y)>("y");

  world.component<Transform>()
    .member(reflected->glm.mat3, "matrix");
  ;

  world.component<HandleIntersections>();
  world.component<IntersectsWith>();

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
}

} //end of namespace engine::world


