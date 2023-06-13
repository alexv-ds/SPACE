#pragma once
#include <string>
#include <cstdint>
#include <flecs.h>
#include <engine/graphics/color.hpp>

namespace engine::graphics {

struct Canvas {
  std::string title;
  std::uint32_t width = 0;
  std::uint32_t height = 0;
  flecs::entity_t camera = flecs::entity::null();
  Color bg_color = color::black;
  float bg_alpha = 1.0f;
};


} //namespace engine::graphics