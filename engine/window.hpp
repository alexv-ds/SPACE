#pragma once
#include <cstdint>
#include <string>
#include <flecs.h>

#include "window/FrameEventsStorage.hpp"
#include "window/Event.hpp"


namespace engine {
  struct Window {
    Window(flecs::world&);
  };
} //namespace engine

namespace engine::window {

  //struct Style 
  enum class Style : std::uint32_t {
    None = 0,
    Titlebar   = 1 << 0, 
    Resize     = 1 << 1, 
    Close      = 1 << 2, 
    Fullscreen = 1 << 3,
    Default = Titlebar | Resize | Close 
  };

  struct MainWindowInit {
    std::uint32_t width = 640;
    std::uint32_t height = 480;
    std::string title = "Main Window ^_^";
    Style style = Style::Default;
  };

  struct MainWindow {
    std::uint32_t width;
    std::uint32_t height;
    FrameEventsStorage events;
  };

} //namespace engine::window