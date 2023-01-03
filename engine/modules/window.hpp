#pragma once
#include <cstdint>
#include <string>
#include <flecs.h>

namespace engine {
  struct Window {
    Window(flecs::world&);
  };
}

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

  enum class Key : std::int32_t {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    Escape,
    LControl,
    LShift,
    LAlt,
    LSystem,
    RControl,
    RShift,
    RAlt,
    RSystem,
    Menu,
    LBracket,
    RBracket,
    Semicolon,
    Comma,
    Period,
    Quote,
    Slash,
    Backslash,
    Tilde,
    Equal,
    Hyphen,
    Space,
    Enter,
    Backspace,
    Tab,
    PageUp,
    PageDown,
    End,
    Home,
    Insert,
    Delete,
    Add,
    Subtract,
    Multiply,
    Divide,
    Left,
    Right,
    Up,
    Down,
    Numpad0,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad4,
    Numpad5,
    Numpad6,
    Numpad7,
    Numpad8,
    Numpad9,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    Pause
  };

  enum class MouseWheel : std::int32_t {
    Vertical,
    Horizontal
  };
  
  enum class MouseButton : std::int32_t {
    Left,
    Right,
    Middle, 
    XButton1,
    XButton2
  };

  struct MainWindowInit {
    unsigned int width = 640;
    unsigned int height = 480;
    std::string title = "Main Window ^_^";
    Style style = Style::Default;
  };
  struct MainWindow {
    unsigned int width;
    unsigned int height;
  };

  struct Event {
    std::size_t index; //
  };

  namespace event {
    struct Closed {}; //The window requested to be closed
    struct Resized {
      unsigned int width;
      unsigned int height;
    };
    struct LostFocus {};
    struct GainedFocus {};

    struct TextEntered {
      std::uint32_t unicode;
    };
    struct KeyPressed {
      Key code;
      bool alt;
      bool control;
      bool shift;
      bool system;
    };
    struct KeyReleased {
      Key code;
    };

    struct MouseWheelScrolled {
      MouseWheel wheel; //Which wheel (for mice with multiple ones) 
      float delta; //Wheel offset (positive is up/left, negative is down/right). High-precision mice may use non-integral offsets.
      int x; //X position of the mouse pointer, relative to the left of the owner window. 
      int y; //Y position of the mouse pointer, relative to the top of the owner window.
    };
    struct MouseButtonPressed {
      MouseButton button; //Code of the button that has been pressed.
      int x; //X position of the mouse pointer, relative to the left of the owner window.
      int y; //Y position of the mouse pointer, relative to the top of the owner window.
    };
    struct MouseButtonReleased {
      MouseButton button; //Code of the button that has been pressed.
      int x; //X position of the mouse pointer, relative to the left of the owner window.
      int y; //Y position of the mouse pointer, relative to the top of the owner window.
    };
    struct MouseMoved {
      int x; //X position of the mouse pointer, relative to the left of the owner window. 
      int y; //Y position of the mouse pointer, relative to the top of the owner window.
    };

    //The mouse cursor entered the area of the window 
    struct MouseEntered {};
    //The mouse cursor left the area of the window 
    struct MouseLeft {}; 
  } //namespace event
} //namespace engine::window