#include "geometry.hpp"

namespace engine {
using namespace geometry;

Geometry::Geometry(flecs::world& world) {
  world.module<Geometry>("geometry");

  world.component<Rectangle>()
    .member<decltype(Rectangle::width)>("width")
    .member<decltype(Rectangle::height)>("height");

  world.component<Square>()
    .member<decltype(Square::size)>("size");

  world.component<Circle>()
    .member<decltype(Circle::radius)>("radius");
}

} //namespace engine