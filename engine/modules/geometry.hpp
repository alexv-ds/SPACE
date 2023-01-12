#pragma once
#include <flecs.h>

namespace engine {

struct Geometry {
  Geometry(flecs::world&);
};

} //namespace engine

namespace engine::geometry {

struct Rectangle {
  float width;
  float height;
};

struct Square {
  float size;
};

struct Circle {
  float radius;
};

};