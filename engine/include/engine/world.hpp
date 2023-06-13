#pragma once
#include <string>
#include <cstdint>
#include "flecs.h"
#include "graphics/color.hpp"

namespace engine {

struct WorldObject {
  float size_x = 1.0f;
  float size_y = 1.0f;
};

struct Scale {
  float x = 0.0f;
  float y = 0.0f;
};

struct Rotation {
  float angle = 0.0f; //radians
};

struct Position {
  float x = 0.0f;
  float y = 0.0f;
};

struct Icon {
  std::string icon;
  std::string icon_state;
};

struct IntersectFilter {
  flecs::query<> query;
};

void keks() {
  //IntersectFilter filter;
  //flecs::filter
}

// Размер обзора камеры от размера WorldObject
struct Camera {};

} //end of namespace engine