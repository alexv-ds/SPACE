#include "transform.hpp"

namespace engine::transform::detail {

} //namespace engine::transform::detail

namespace engine {
using namespace transform;

Transform::Transform(flecs::world& world) {
  world.module<Transform>("transform");
  
  world.component<Position2>()
    .member<decltype(Position2::x)>("x")
    .member<decltype(Position2::y)>("y");

  world.component<Scale2>()
    .member<decltype(Scale2::x)>("x")
    .member<decltype(Scale2::y)>("y");

  world.component<Rotation2>()
    .member<decltype(Rotation2::angle), flecs::units::angle::Radians>("angle");

  world.component<Transform2>();
}

} //namespace engine