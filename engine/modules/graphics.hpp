#pragma once
#include <flecs.h>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include "graphics/Color.hpp"

namespace engine {

struct Graphics {
  Graphics(flecs::world&);
};

} //namespace engine


namespace engine::graphics {

//defined in Color.hpp
//struct Color {
//  std::uint8_t r = 0;
//  std::uint8_t g = 0;
//  std::uint8_t b = 0;
//};

struct Transparency {
  std::uint8_t a = 255;
};

struct Renderable {};

struct Camera {};

struct MainWindowCamera {
  //glm::mat3 screen_space_transform;
  glm::vec2 camera_size;
};

} //namespace engine::graphics