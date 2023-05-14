#pragma once
#include <cstdint>

namespace engine::window {

enum class MouseButton : std::int32_t {
  Unknown = -1,
  Left = 0, //!< The left mouse button
  Right,    //!< The right mouse button
  Middle,   //!< The middle (wheel) mouse button
  XButton1, //!< The first extra mouse button
  XButton2, //!< The second extra mouse button

  Count //!< Keep last -- the total number of mouse buttons
};

enum class MouseWheel : std::int32_t {
  Vertical,  //!< The vertical mouse wheel
  Horizontal //!< The horizontal mouse wheel
};


} //namespace engine::window