#pragma once
#include <flecs.h>

namespace engine {

struct Imgui {
  Imgui(flecs::world&);
};

} //namespace engine

namespace engine::imgui {

//singleton
struct ImguiContext {};

} //namespace engine::imgui


