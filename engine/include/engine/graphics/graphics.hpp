#pragma once
#include <string>
#include "color.hpp"

namespace engine::graphics {

struct Drawable {};

struct Icon {
  std::string icon;
  std::string icon_state;
};

struct Camera {
  float size_x = 1.0f;
  float size_y = 1.0f;
};

} //end of namespace engine::graphics