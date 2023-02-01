#pragma once
#include <cstdint>

namespace engine::window {

enum class Key : std::int32_t {
  Unknown = -1, //!< Unhandled key
  A       = 0,  //!< The A key
  B,            //!< The B key
  C,            //!< The C key
  D,            //!< The D key
  E,            //!< The E key
  F,            //!< The F key
  G,            //!< The G key
  H,            //!< The H key
  I,            //!< The I key
  J,            //!< The J key
  K,            //!< The K key
  L,            //!< The L key
  M,            //!< The M key
  N,            //!< The N key
  O,            //!< The O key
  P,            //!< The P key
  Q,            //!< The Q key
  R,            //!< The R key
  S,            //!< The S key
  T,            //!< The T key
  U,            //!< The U key
  V,            //!< The V key
  W,            //!< The W key
  X,            //!< The X key
  Y,            //!< The Y key
  Z,            //!< The Z key
  Num0,         //!< The 0 key
  Num1,         //!< The 1 key
  Num2,         //!< The 2 key
  Num3,         //!< The 3 key
  Num4,         //!< The 4 key
  Num5,         //!< The 5 key
  Num6,         //!< The 6 key
  Num7,         //!< The 7 key
  Num8,         //!< The 8 key
  Num9,         //!< The 9 key
  Escape,       //!< The Escape key
  LControl,     //!< The left Control key
  LShift,       //!< The left Shift key
  LAlt,         //!< The left Alt key
  LSystem,      //!< The left OS specific key: window (Windows and Linux), apple (macOS), ...
  RControl,     //!< The right Control key
  RShift,       //!< The right Shift key
  RAlt,         //!< The right Alt key
  RSystem,      //!< The right OS specific key: window (Windows and Linux), apple (macOS), ...
  Menu,         //!< The Menu key
  LBracket,     //!< The [ key
  RBracket,     //!< The ] key
  Semicolon,    //!< The ; key
  Comma,        //!< The , key
  Period,       //!< The . key
  Apostrophe,   //!< The ' key
  Slash,        //!< The / key
  Backslash,    //!< The \ key
  Grave,        //!< The ` key
  Equal,        //!< The = key
  Hyphen,       //!< The - key (hyphen)
  Space,        //!< The Space key
  Enter,        //!< The Enter/Return keys
  Backspace,    //!< The Backspace key
  Tab,          //!< The Tabulation key
  PageUp,       //!< The Page up key
  PageDown,     //!< The Page down key
  End,          //!< The End key
  Home,         //!< The Home key
  Insert,       //!< The Insert key
  Delete,       //!< The Delete key
  Add,          //!< The + key
  Subtract,     //!< The - key (minus, usually from numpad)
  Multiply,     //!< The * key
  Divide,       //!< The / key
  Left,         //!< Left arrow
  Right,        //!< Right arrow
  Up,           //!< Up arrow
  Down,         //!< Down arrow
  Numpad0,      //!< The numpad 0 key
  Numpad1,      //!< The numpad 1 key
  Numpad2,      //!< The numpad 2 key
  Numpad3,      //!< The numpad 3 key
  Numpad4,      //!< The numpad 4 key
  Numpad5,      //!< The numpad 5 key
  Numpad6,      //!< The numpad 6 key
  Numpad7,      //!< The numpad 7 key
  Numpad8,      //!< The numpad 8 key
  Numpad9,      //!< The numpad 9 key
  F1,           //!< The F1 key
  F2,           //!< The F2 key
  F3,           //!< The F3 key
  F4,           //!< The F4 key
  F5,           //!< The F5 key
  F6,           //!< The F6 key
  F7,           //!< The F7 key
  F8,           //!< The F8 key
  F9,           //!< The F9 key
  F10,          //!< The F10 key
  F11,          //!< The F11 key
  F12,          //!< The F12 key
  F13,          //!< The F13 key
  F14,          //!< The F14 key
  F15,          //!< The F15 key
  Pause,        //!< The Pause key

  Count, //!< Keep last -- the total number of keyboard keys
};

enum class Scancode : std::int32_t {
  Unknown = -1, //!< Represents any scancode not present in this enum
  A       = 0,  //!< Keyboard a and A key
  B,            //!< Keyboard b and B key
  C,            //!< Keyboard c and C key
  D,            //!< Keyboard d and D key
  E,            //!< Keyboard e and E key
  F,            //!< Keyboard f and F key
  G,            //!< Keyboard g and G key
  H,            //!< Keyboard h and H key
  I,            //!< Keyboard i and I key
  J,            //!< Keyboard j and J key
  K,            //!< Keyboard k and K key
  L,            //!< Keyboard l and L key
  M,            //!< Keyboard m and M key
  N,            //!< Keyboard n and N key
  O,            //!< Keyboard o and O key
  P,            //!< Keyboard p and P key
  Q,            //!< Keyboard q and Q key
  R,            //!< Keyboard r and R key
  S,            //!< Keyboard s and S key
  T,            //!< Keyboard t and T key
  U,            //!< Keyboard u and U key
  V,            //!< Keyboard v and V key
  W,            //!< Keyboard w and W key
  X,            //!< Keyboard x and X key
  Y,            //!< Keyboard y and Y key
  Z,            //!< Keyboard z and Z key
  Num1,         //!< Keyboard 1 and ! key
  Num2,         //!< Keyboard 2 and @ key
  Num3,         //!< Keyboard 3 and # key
  Num4,         //!< Keyboard 4 and $ key
  Num5,         //!< Keyboard 5 and % key
  Num6,         //!< Keyboard 6 and ^ key
  Num7,         //!< Keyboard 7 and & key
  Num8,         //!< Keyboard 8 and * key
  Num9,         //!< Keyboard 9 and ) key
  Num0,         //!< Keyboard 0 and ) key
  Enter,        //!< Keyboard Enter/Return key
  Escape,       //!< Keyboard Escape key
  Backspace,    //!< Keyboard Backspace key
  Tab,          //!< Keyboard Tab key
  Space,        //!< Keyboard Space key
  Hyphen,       //!< Keyboard - and _ key
  Equal,        //!< Keyboard = and +
  LBracket,     //!< Keyboard [ and { key
  RBracket,     //!< Keyboard ] and } key
  Backslash,      //!< Keyboard \ and | key OR various keys for Non-US keyboards
  Semicolon,      //!< Keyboard ; and : key
  Apostrophe,     //!< Keyboard ' and " key
  Grave,          //!< Keyboard ` and ~ key
  Comma,          //!< Keyboard , and < key
  Period,         //!< Keyboard . and > key
  Slash,          //!< Keyboard / and ? key
  F1,             //!< Keyboard F1 key
  F2,             //!< Keyboard F2 key
  F3,             //!< Keyboard F3 key
  F4,             //!< Keyboard F4 key
  F5,             //!< Keyboard F5 key
  F6,             //!< Keyboard F6 key
  F7,             //!< Keyboard F7 key
  F8,             //!< Keyboard F8 key
  F9,             //!< Keyboard F9 key
  F10,            //!< Keyboard F10 key
  F11,            //!< Keyboard F11 key
  F12,            //!< Keyboard F12 key
  F13,            //!< Keyboard F13 key
  F14,            //!< Keyboard F14 key
  F15,            //!< Keyboard F15 key
  F16,            //!< Keyboard F16 key
  F17,            //!< Keyboard F17 key
  F18,            //!< Keyboard F18 key
  F19,            //!< Keyboard F19 key
  F20,            //!< Keyboard F20 key
  F21,            //!< Keyboard F21 key
  F22,            //!< Keyboard F22 key
  F23,            //!< Keyboard F23 key
  F24,            //!< Keyboard F24 key
  CapsLock,       //!< Keyboard Caps %Lock key
  PrintScreen,    //!< Keyboard Print Screen key
  ScrollLock,     //!< Keyboard Scroll %Lock key
  Pause,          //!< Keyboard Pause key
  Insert,         //!< Keyboard Insert key
  Home,           //!< Keyboard Home key
  PageUp,         //!< Keyboard Page Up key
  Delete,         //!< Keyboard Delete Forward key
  End,            //!< Keyboard End key
  PageDown,       //!< Keyboard Page Down key
  Right,          //!< Keyboard Right Arrow key
  Left,           //!< Keyboard Left Arrow key
  Down,           //!< Keyboard Down Arrow key
  Up,             //!< Keyboard Up Arrow key
  NumLock,        //!< Keypad Num %Lock and Clear key
  NumpadDivide,   //!< Keypad / key
  NumpadMultiply, //!< Keypad * key
  NumpadMinus,    //!< Keypad - key
  NumpadPlus,     //!< Keypad + key
  NumpadEqual,    //!< keypad = key
  NumpadEnter,    //!< Keypad Enter/Return key
  NumpadDecimal,  //!< Keypad . and Delete key
  Numpad1,        //!< Keypad 1 and End key
  Numpad2,        //!< Keypad 2 and Down Arrow key
  Numpad3,        //!< Keypad 3 and Page Down key
  Numpad4,        //!< Keypad 4 and Left Arrow key
  Numpad5,        //!< Keypad 5 key
  Numpad6,        //!< Keypad 6 and Right Arrow key
  Numpad7,        //!< Keypad 7 and Home key
  Numpad8,        //!< Keypad 8 and Up Arrow key
  Numpad9,        //!< Keypad 9 and Page Up key
  Numpad0,        //!< Keypad 0 and Insert key
  NonUsBackslash,     //!< Keyboard Non-US \ and | key
  Application,        //!< Keyboard Application key
  Execute,            //!< Keyboard Execute key
  ModeChange,         //!< Keyboard Mode Change key
  Help,               //!< Keyboard Help key
  Menu,               //!< Keyboard Menu key
  Select,             //!< Keyboard Select key
  Redo,               //!< Keyboard Redo key
  Undo,               //!< Keyboard Undo key
  Cut,                //!< Keyboard Cut key
  Copy,               //!< Keyboard Copy key
  Paste,              //!< Keyboard Paste key
  VolumeMute,         //!< Keyboard Volume Mute key
  VolumeUp,           //!< Keyboard Volume Up key
  VolumeDown,         //!< Keyboard Volume Down key
  MediaPlayPause,     //!< Keyboard Media Play Pause key
  MediaStop,          //!< Keyboard Media Stop key
  MediaNextTrack,     //!< Keyboard Media Next Track key
  MediaPreviousTrack, //!< Keyboard Media Previous Track key
  LControl,           //!< Keyboard Left Control key
  LShift,             //!< Keyboard Left Shift key
  LAlt,               //!< Keyboard Left Alt key
  LSystem,            //!< Keyboard Left System key
  RControl,           //!< Keyboard Right Control key
  RShift,             //!< Keyboard Right Shift key
  RAlt,               //!< Keyboard Right Alt key
  RSystem,            //!< Keyboard Right System key
  Back,               //!< Keyboard Back key
  Forward,            //!< Keyboard Forward key
  Refresh,            //!< Keyboard Refresh key
  Stop,               //!< Keyboard Stop key
  Search,             //!< Keyboard Search key
  Favorites,          //!< Keyboard Favorites key
  HomePage,           //!< Keyboard Home Page key
  LaunchApplication1, //!< Keyboard Launch Application 1 key
  LaunchApplication2, //!< Keyboard Launch Application 2 key
  LaunchMail,         //!< Keyboard Launch Mail key
  LaunchMediaSelect,  //!< Keyboard Launch Media Select key

  Count //!< Keep last -- the total number of scancodes
};

} //namespace engine::window
