#include <vector>
#include <type_traits>
#include <cassert>
#include <spdlog/spdlog.h>
#include <SFML/Window.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include "window-backend-sfml.hpp"
#include "window.hpp"


namespace engine::window_backend_sfml::detail {

/////////////////////////////////////
///////////KEYS MAPPINGS/////////////
/////////////////////////////////////

class KeyMapping {
public:
  static const KeyMapping& get() {
    static KeyMapping mapping;
    return mapping;
  }

  std::vector<window::Key> keys_sfml_to_engine;
  std::vector<window::Scancode> scancodes_sfml_to_engine;
  std::vector<window::MouseButton> mousebuttons_sfml_to_engine;

private:
  using ScancodeUnderlying = std::underlying_type_t<sf::Keyboard::Scancode>;
  KeyMapping();
};

KeyMapping::KeyMapping():
    keys_sfml_to_engine(sf::Keyboard::KeyCount, window::Key::Unknown),
    scancodes_sfml_to_engine(static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::ScancodeCount), window::Scancode::Unknown),
    mousebuttons_sfml_to_engine(sf::Mouse::ButtonCount, window::MouseButton::Unknown)
{
  //window::key
  keys_sfml_to_engine[sf::Keyboard::A] = window::Key::A;
  keys_sfml_to_engine[sf::Keyboard::B] = window::Key::B;
  keys_sfml_to_engine[sf::Keyboard::C] = window::Key::C;
  keys_sfml_to_engine[sf::Keyboard::D] = window::Key::D;
  keys_sfml_to_engine[sf::Keyboard::E] = window::Key::E;
  keys_sfml_to_engine[sf::Keyboard::F] = window::Key::F;
  keys_sfml_to_engine[sf::Keyboard::G] = window::Key::G;
  keys_sfml_to_engine[sf::Keyboard::H] = window::Key::H;
  keys_sfml_to_engine[sf::Keyboard::I] = window::Key::I;
  keys_sfml_to_engine[sf::Keyboard::J] = window::Key::J;
  keys_sfml_to_engine[sf::Keyboard::K] = window::Key::K;
  keys_sfml_to_engine[sf::Keyboard::L] = window::Key::L;
  keys_sfml_to_engine[sf::Keyboard::M] = window::Key::M;
  keys_sfml_to_engine[sf::Keyboard::N] = window::Key::N;
  keys_sfml_to_engine[sf::Keyboard::O] = window::Key::O;
  keys_sfml_to_engine[sf::Keyboard::P] = window::Key::P;
  keys_sfml_to_engine[sf::Keyboard::Q] = window::Key::Q;
  keys_sfml_to_engine[sf::Keyboard::R] = window::Key::R;
  keys_sfml_to_engine[sf::Keyboard::S] = window::Key::S;
  keys_sfml_to_engine[sf::Keyboard::T] = window::Key::T;
  keys_sfml_to_engine[sf::Keyboard::U] = window::Key::U;
  keys_sfml_to_engine[sf::Keyboard::V] = window::Key::V;
  keys_sfml_to_engine[sf::Keyboard::W] = window::Key::W;
  keys_sfml_to_engine[sf::Keyboard::X] = window::Key::X;
  keys_sfml_to_engine[sf::Keyboard::Y] = window::Key::Y;
  keys_sfml_to_engine[sf::Keyboard::Z] = window::Key::Z;
  keys_sfml_to_engine[sf::Keyboard::Num0] = window::Key::Num0;
  keys_sfml_to_engine[sf::Keyboard::Num1] = window::Key::Num1;
  keys_sfml_to_engine[sf::Keyboard::Num2] = window::Key::Num2;
  keys_sfml_to_engine[sf::Keyboard::Num3] = window::Key::Num3;
  keys_sfml_to_engine[sf::Keyboard::Num4] = window::Key::Num4;
  keys_sfml_to_engine[sf::Keyboard::Num5] = window::Key::Num5;
  keys_sfml_to_engine[sf::Keyboard::Num6] = window::Key::Num6;
  keys_sfml_to_engine[sf::Keyboard::Num7] = window::Key::Num7;
  keys_sfml_to_engine[sf::Keyboard::Num8] = window::Key::Num8;
  keys_sfml_to_engine[sf::Keyboard::Num9] = window::Key::Num9;
  keys_sfml_to_engine[sf::Keyboard::Escape] = window::Key::Escape;
  keys_sfml_to_engine[sf::Keyboard::LControl] = window::Key::LControl;
  keys_sfml_to_engine[sf::Keyboard::LShift] = window::Key::LShift;
  keys_sfml_to_engine[sf::Keyboard::LAlt] = window::Key::LAlt;
  keys_sfml_to_engine[sf::Keyboard::LSystem] = window::Key::LSystem;
  keys_sfml_to_engine[sf::Keyboard::RControl] = window::Key::RControl;
  keys_sfml_to_engine[sf::Keyboard::RShift] = window::Key::RShift;
  keys_sfml_to_engine[sf::Keyboard::RAlt] = window::Key::RAlt;
  keys_sfml_to_engine[sf::Keyboard::RSystem] = window::Key::RSystem;
  keys_sfml_to_engine[sf::Keyboard::Menu] = window::Key::Menu;
  keys_sfml_to_engine[sf::Keyboard::LBracket] = window::Key::LBracket;
  keys_sfml_to_engine[sf::Keyboard::RBracket] = window::Key::RBracket;
  keys_sfml_to_engine[sf::Keyboard::Semicolon] = window::Key::Semicolon;
  keys_sfml_to_engine[sf::Keyboard::Comma] = window::Key::Comma;
  keys_sfml_to_engine[sf::Keyboard::Period] = window::Key::Period;
  keys_sfml_to_engine[sf::Keyboard::Apostrophe] = window::Key::Apostrophe;
  keys_sfml_to_engine[sf::Keyboard::Slash] = window::Key::Slash;
  keys_sfml_to_engine[sf::Keyboard::Backslash] = window::Key::Backslash;
  keys_sfml_to_engine[sf::Keyboard::Grave] = window::Key::Grave;
  keys_sfml_to_engine[sf::Keyboard::Equal] = window::Key::Equal;
  keys_sfml_to_engine[sf::Keyboard::Hyphen] = window::Key::Hyphen;
  keys_sfml_to_engine[sf::Keyboard::Space] = window::Key::Space;
  keys_sfml_to_engine[sf::Keyboard::Enter] = window::Key::Enter;
  keys_sfml_to_engine[sf::Keyboard::Backspace] = window::Key::Backspace;
  keys_sfml_to_engine[sf::Keyboard::Tab] = window::Key::Tab;
  keys_sfml_to_engine[sf::Keyboard::PageUp] = window::Key::PageUp;
  keys_sfml_to_engine[sf::Keyboard::PageDown] = window::Key::PageDown;
  keys_sfml_to_engine[sf::Keyboard::End] = window::Key::End;
  keys_sfml_to_engine[sf::Keyboard::Home] = window::Key::Home;
  keys_sfml_to_engine[sf::Keyboard::Insert] = window::Key::Insert;
  keys_sfml_to_engine[sf::Keyboard::Delete] = window::Key::Delete;
  keys_sfml_to_engine[sf::Keyboard::Add] = window::Key::Add;
  keys_sfml_to_engine[sf::Keyboard::Subtract] = window::Key::Subtract;
  keys_sfml_to_engine[sf::Keyboard::Multiply] = window::Key::Multiply;
  keys_sfml_to_engine[sf::Keyboard::Divide] = window::Key::Divide;
  keys_sfml_to_engine[sf::Keyboard::Left] = window::Key::Left;
  keys_sfml_to_engine[sf::Keyboard::Right] = window::Key::Right;
  keys_sfml_to_engine[sf::Keyboard::Up] = window::Key::Up;
  keys_sfml_to_engine[sf::Keyboard::Down] = window::Key::Down;
  keys_sfml_to_engine[sf::Keyboard::Numpad0] = window::Key::Numpad0;
  keys_sfml_to_engine[sf::Keyboard::Numpad1] = window::Key::Numpad1;
  keys_sfml_to_engine[sf::Keyboard::Numpad2] = window::Key::Numpad2;
  keys_sfml_to_engine[sf::Keyboard::Numpad3] = window::Key::Numpad3;
  keys_sfml_to_engine[sf::Keyboard::Numpad4] = window::Key::Numpad4;
  keys_sfml_to_engine[sf::Keyboard::Numpad5] = window::Key::Numpad5;
  keys_sfml_to_engine[sf::Keyboard::Numpad6] = window::Key::Numpad6;
  keys_sfml_to_engine[sf::Keyboard::Numpad7] = window::Key::Numpad7;
  keys_sfml_to_engine[sf::Keyboard::Numpad8] = window::Key::Numpad8;
  keys_sfml_to_engine[sf::Keyboard::Numpad9] = window::Key::Numpad9;
  keys_sfml_to_engine[sf::Keyboard::F1] = window::Key::F1;
  keys_sfml_to_engine[sf::Keyboard::F2] = window::Key::F2;
  keys_sfml_to_engine[sf::Keyboard::F3] = window::Key::F3;
  keys_sfml_to_engine[sf::Keyboard::F4] = window::Key::F4;
  keys_sfml_to_engine[sf::Keyboard::F5] = window::Key::F5;
  keys_sfml_to_engine[sf::Keyboard::F6] = window::Key::F6;
  keys_sfml_to_engine[sf::Keyboard::F7] = window::Key::F7;
  keys_sfml_to_engine[sf::Keyboard::F8] = window::Key::F8;
  keys_sfml_to_engine[sf::Keyboard::F9] = window::Key::F9;
  keys_sfml_to_engine[sf::Keyboard::F10] = window::Key::F10;
  keys_sfml_to_engine[sf::Keyboard::F11] = window::Key::F11;
  keys_sfml_to_engine[sf::Keyboard::F12] = window::Key::F12;
  keys_sfml_to_engine[sf::Keyboard::F13] = window::Key::F13;
  keys_sfml_to_engine[sf::Keyboard::F14] = window::Key::F14;
  keys_sfml_to_engine[sf::Keyboard::F15] = window::Key::F15;
  keys_sfml_to_engine[sf::Keyboard::Pause] = window::Key::Pause;

  //window::Scancode
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::A)] = window::Scancode::A;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::B)] = window::Scancode::B;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::C)] = window::Scancode::C;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::D)] = window::Scancode::D;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::E)] = window::Scancode::E;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F)] = window::Scancode::F;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::G)] = window::Scancode::G;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::H)] = window::Scancode::H;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::I)] = window::Scancode::I;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::J)] = window::Scancode::J;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::K)] = window::Scancode::K;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::L)] = window::Scancode::L;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::M)] = window::Scancode::M;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::N)] = window::Scancode::N;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::O)] = window::Scancode::O;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::P)] = window::Scancode::P;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Q)] = window::Scancode::Q;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::R)] = window::Scancode::R;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::S)] = window::Scancode::S;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::T)] = window::Scancode::T;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::U)] = window::Scancode::U;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::V)] = window::Scancode::V;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::W)] = window::Scancode::W;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::X)] = window::Scancode::X;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Y)] = window::Scancode::Y;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Z)] = window::Scancode::Z;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Num1)] = window::Scancode::Num1;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Num2)] = window::Scancode::Num2;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Num3)] = window::Scancode::Num3;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Num4)] = window::Scancode::Num4;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Num5)] = window::Scancode::Num5;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Num6)] = window::Scancode::Num6;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Num7)] = window::Scancode::Num7;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Num8)] = window::Scancode::Num8;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Num9)] = window::Scancode::Num9;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Num0)] = window::Scancode::Num0;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Enter)] = window::Scancode::Enter;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Escape)] = window::Scancode::Escape;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Backspace)] = window::Scancode::Backspace;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Tab)] = window::Scancode::Tab;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Space)] = window::Scancode::Space;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Hyphen)] = window::Scancode::Hyphen;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Equal)] = window::Scancode::Equal;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::LBracket)] = window::Scancode::LBracket;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::RBracket)] = window::Scancode::RBracket;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Backslash)] = window::Scancode::Backslash;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Semicolon)] = window::Scancode::Semicolon;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Apostrophe)] = window::Scancode::Apostrophe;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Grave)] = window::Scancode::Grave;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Comma)] = window::Scancode::Comma;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Period)] = window::Scancode::Period;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Slash)] = window::Scancode::Slash;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F1)] = window::Scancode::F1;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F2)] = window::Scancode::F2;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F3)] = window::Scancode::F3;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F4)] = window::Scancode::F4;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F5)] = window::Scancode::F5;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F6)] = window::Scancode::F6;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F7)] = window::Scancode::F7;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F8)] = window::Scancode::F8;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F9)] = window::Scancode::F9;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F10)] = window::Scancode::F10;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F11)] = window::Scancode::F11;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F12)] = window::Scancode::F12;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F13)] = window::Scancode::F13;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F14)] = window::Scancode::F14;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F15)] = window::Scancode::F15;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F16)] = window::Scancode::F16;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F17)] = window::Scancode::F17;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F18)] = window::Scancode::F18;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F19)] = window::Scancode::F19;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F20)] = window::Scancode::F20;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F21)] = window::Scancode::F21;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F22)] = window::Scancode::F22;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F23)] = window::Scancode::F23;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::F24)] = window::Scancode::F24;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::CapsLock)] = window::Scancode::CapsLock;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::PrintScreen)] = window::Scancode::PrintScreen;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::ScrollLock)] = window::Scancode::ScrollLock;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Pause)] = window::Scancode::Pause;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Insert)] = window::Scancode::Insert;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Home)] = window::Scancode::Home;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::PageUp)] = window::Scancode::PageUp;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Delete)] = window::Scancode::Delete;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::End)] = window::Scancode::End;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::PageDown)] = window::Scancode::PageDown;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Right)] = window::Scancode::Right;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Left)] = window::Scancode::Left;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Down)] = window::Scancode::Down;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Up)] = window::Scancode::Up;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::NumLock)] = window::Scancode::NumLock;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::NumpadDivide)] = window::Scancode::NumpadDivide;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::NumpadMultiply)] = window::Scancode::NumpadMultiply;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::NumpadMinus)] = window::Scancode::NumpadMinus;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::NumpadPlus)] = window::Scancode::NumpadPlus;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::NumpadEqual)] = window::Scancode::NumpadEqual;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::NumpadEnter)] = window::Scancode::NumpadEnter;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::NumpadDecimal)] = window::Scancode::NumpadDecimal;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Numpad1)] = window::Scancode::Numpad1;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Numpad2)] = window::Scancode::Numpad2;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Numpad3)] = window::Scancode::Numpad3;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Numpad4)] = window::Scancode::Numpad4;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Numpad5)] = window::Scancode::Numpad5;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Numpad6)] = window::Scancode::Numpad6;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Numpad7)] = window::Scancode::Numpad7;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Numpad8)] = window::Scancode::Numpad8;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Numpad9)] = window::Scancode::Numpad9;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Numpad0)] = window::Scancode::Numpad0;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::NonUsBackslash)] = window::Scancode::NonUsBackslash;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Application)] = window::Scancode::Application;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Execute)] = window::Scancode::Execute;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::ModeChange)] = window::Scancode::ModeChange;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Help)] = window::Scancode::Help;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Menu)] = window::Scancode::Menu;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Select)] = window::Scancode::Select;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Redo)] = window::Scancode::Redo;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Undo)] = window::Scancode::Undo;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Cut)] = window::Scancode::Cut;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Copy)] = window::Scancode::Copy;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Paste)] = window::Scancode::Paste;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::VolumeMute)] = window::Scancode::VolumeMute;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::VolumeUp)] = window::Scancode::VolumeUp;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::VolumeDown)] = window::Scancode::VolumeDown;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::MediaPlayPause)] = window::Scancode::MediaPlayPause;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::MediaStop)] = window::Scancode::MediaStop;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::MediaNextTrack)] = window::Scancode::MediaNextTrack;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::MediaPreviousTrack)] = window::Scancode::MediaPreviousTrack;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::LControl)] = window::Scancode::LControl;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::LShift)] = window::Scancode::LShift;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::LAlt)] = window::Scancode::LAlt;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::LSystem)] = window::Scancode::LSystem;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::RControl)] = window::Scancode::RControl;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::RShift)] = window::Scancode::RShift;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::RAlt)] = window::Scancode::RAlt;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::RSystem)] = window::Scancode::RSystem;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Back)] = window::Scancode::Back;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Forward)] = window::Scancode::Forward;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Refresh)] = window::Scancode::Refresh;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Stop)] = window::Scancode::Stop;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Search)] = window::Scancode::Search;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::Favorites)] = window::Scancode::Favorites;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::HomePage)] = window::Scancode::HomePage;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::LaunchApplication1)] = window::Scancode::LaunchApplication1;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::LaunchApplication2)] = window::Scancode::LaunchApplication2;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::LaunchMail)] = window::Scancode::LaunchMail;
  scancodes_sfml_to_engine[static_cast<ScancodeUnderlying>(sf::Keyboard::Scancode::LaunchMediaSelect)] = window::Scancode::LaunchMediaSelect;

  //window::MouseButton
  mousebuttons_sfml_to_engine[sf::Mouse::Left] = window::MouseButton::Left;
  mousebuttons_sfml_to_engine[sf::Mouse::Right] = window::MouseButton::Right;
  mousebuttons_sfml_to_engine[sf::Mouse::Middle] = window::MouseButton::Middle;
  mousebuttons_sfml_to_engine[sf::Mouse::XButton1] = window::MouseButton::XButton1;
  mousebuttons_sfml_to_engine[sf::Mouse::XButton2] = window::MouseButton::XButton2;
}

/////////////////////////////////////
/////////////OTHER STUFF/////////////
/////////////////////////////////////

static window::Key key_sfml2engine(const KeyMapping& mapping, const sf::Keyboard::Key key) {
  if (std::size_t key_idx = static_cast<std::size_t>(key); mapping.keys_sfml_to_engine.size() > key_idx) [[likely]] {
    return mapping.keys_sfml_to_engine[key_idx];
  } else [[unlikely]] {
    SPDLOG_WARN("Unknown key code. Condition not met: keys_sfml_to_engine.size() > key_idx");
    return window::Key::Unknown;
  }
}

static window::Scancode scancode_sfml2engine(const KeyMapping& mapping, const sf::Keyboard::Scancode scancode) {
  if (std::size_t scancode_idx = static_cast<std::size_t>(scancode); mapping.scancodes_sfml_to_engine.size() > scancode_idx) [[likely]] {
    return mapping.scancodes_sfml_to_engine[scancode_idx];
  } else [[unlikely]] {
    SPDLOG_WARN("Unkcown scancode. Condition not met: scancodes_sfml_to_engine.size() > scancode_idx");
    return window::Scancode::Unknown;
  }
}

static window::MouseButton mousebutton_sfml2engine(const KeyMapping& mapping, const sf::Mouse::Button button) {
  if (std::size_t button_idx = static_cast<std::size_t>(button); mapping.mousebuttons_sfml_to_engine.size() > button_idx) [[likely]] {
    return mapping.mousebuttons_sfml_to_engine[button_idx];
  } else [[unlikely]] {
    SPDLOG_WARN("Unkcown mouse button. Condition not met: mousebuttons_sfml_to_engine.size() > button_idx");
    return window::MouseButton::Unknown;
  }
}

static void push_event(window::FrameEventsStorage& storage, const sf::Event& event) {
  switch (event.type) {
    case sf::Event::Closed: {
      storage.push<window::event::Closed>();
      break;
    }
    case sf::Event::Resized: {
      storage.push<window::event::Resized>({
        .width = event.size.width,
        .height = event.size.height
      });
      break;
    }
    case sf::Event::LostFocus: {
      storage.push<window::event::LostFocus>();
      break;
    }
    case sf::Event::GainedFocus: {
      storage.push<window::event::GainedFocus>();
      break;
    }
    case sf::Event::TextEntered: {
      storage.push<window::event::TextEntered>({
        .unicode = event.text.unicode
      });
      break;
    }
    case sf::Event::KeyPressed: {
      storage.push<window::event::KeyPressed>({
        .key = key_sfml2engine(KeyMapping::get(), event.key.code),
        .scancode = scancode_sfml2engine(KeyMapping::get(), event.key.scancode),
        .alt = event.key.alt,
        .control = event.key.control,
        .shift = event.key.shift,
        .system = event.key.system
      });
      break;
    }
    case sf::Event::KeyReleased: {
      storage.push<window::event::KeyReleased>({
        .key = key_sfml2engine(KeyMapping::get(), event.key.code),
        .scancode = scancode_sfml2engine(KeyMapping::get(), event.key.scancode),
        .alt = event.key.alt,
        .control = event.key.control,
        .shift = event.key.shift,
        .system = event.key.system
      });
      break;
    }
    case sf::Event::MouseWheelScrolled: {
      storage.push<window::event::MouseWheelScrolled>({
        .wheel = event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel ?
                                                  window::MouseWheel::Vertical : window::MouseWheel::Horizontal,
        .delta = event.mouseWheelScroll.delta,
        .x = event.mouseWheelScroll.x,
        .y = event.mouseWheelScroll.y
      });
      break;
    }
    case sf::Event::MouseButtonPressed: {
      storage.push<window::event::MouseButtonPressed>({
        .button = mousebutton_sfml2engine(KeyMapping::get(), event.mouseButton.button),
        .x = event.mouseButton.x,
        .y = event.mouseButton.y
      });
      break;
    }
    case sf::Event::MouseButtonReleased: {
      storage.push<window::event::MouseButtonReleased>({
        .button = mousebutton_sfml2engine(KeyMapping::get(), event.mouseButton.button),
        .x = event.mouseButton.x,
        .y = event.mouseButton.y
      });
      break;
    }
    case sf::Event::MouseMoved: {
      storage.push<window::event::MouseMoved>({
        .x = event.mouseMove.x,
        .y = event.mouseMove.y
      });
      break;
    }
    case sf::Event::MouseEntered: {
      storage.push<window::event::MouseEntered>();
      break;
    }
    case sf::Event::MouseLeft: {
      storage.push<window::event::MouseLeft>();
      break;
    }
  } //end of switch
}

/////////////////////////////////////
/////////////SYSTEMS/////////////////
/////////////////////////////////////

static void InitSystem(flecs::iter it, const window::MainWindowInit* initdata) {
  it.world().remove<window::MainWindowInit>();
  it.world().set<window::MainWindow>({
    .width = initdata->width,
    .height = initdata->height
  });

  sf::VideoMode video_mode({initdata->width, initdata->height});

  static_assert(sf::Style::Close == static_cast<std::uint32_t>(window::Style::Close));
  static_assert(sf::Style::Default == static_cast<std::uint32_t>(window::Style::Default));
  static_assert(sf::Style::Fullscreen == static_cast<std::uint32_t>(window::Style::Fullscreen));
  static_assert(sf::Style::None == static_cast<std::uint32_t>(window::Style::None));
  static_assert(sf::Style::Resize == static_cast<std::uint32_t>(window::Style::Resize));
  static_assert(sf::Style::Titlebar == static_cast<std::uint32_t>(window::Style::Titlebar));
  std::uint32_t style = static_cast<std::uint32_t>(initdata->style);

  if (initdata->init_render_window) {
    std::shared_ptr render_window = std::make_shared<sf::RenderWindow>(video_mode, initdata->title, style);
    it.world().set<MainWindowSFML_RenderWindow>({.window = render_window});
    it.world().set<MainWindowSFML>({.window = render_window});
  } else {
    std::shared_ptr base_window = std::make_shared<sf::WindowBase>(video_mode, initdata->title, style);
    it.world().set<MainWindowSFML>({.window = base_window});
  }
}

//Довольно странно если за один кадр будет больше 20 ивентов
//Мб, отключена система очистки?
#define SFML_BACKEND___STORAGE_SUSPICIOUS_SIZE 20
#define SFML_BACKEND___REPORT_DELAY 3 //in secs

static void PollEvents(flecs::iter it,
                      window::MainWindow* window,
                      const MainWindowSFML* sfml_window,
                      WindowBackendSfml* module)
{
  assert(sfml_window->window != nullptr);
  sf::Event event;
  while(sfml_window->window->pollEvent(event)) {
    push_event(window->events, event);
  }

  if (window->events.raw_size() > SFML_BACKEND___STORAGE_SUSPICIOUS_SIZE) {
    module->suspicious_size_msg_delay -= it.delta_system_time();
    if (module->suspicious_size_msg_delay <= 0) {
      module->suspicious_size_msg_delay = SFML_BACKEND___REPORT_DELAY;
      SPDLOG_WARN("Events Storage has suspicious size: {}", window->events.raw_size());
    }
  }
}

#undef SFML_BACKEND___REPORT_DELAY
#undef SFML_BACKEND___STORAGE_SUSPICIOUS_SIZE

} //namespace engine::window_backend_sfml::detail

namespace engine {
  using namespace window_backend_sfml;

  WindowBackendSfml::WindowBackendSfml(flecs::world& world) {
    world.import<Window>();
    world.module<WindowBackendSfml>("window_backend_sfml");

    //components
    world.component<MainWindowSFML>();
    world.component<MainWindowSFML_RenderWindow>();

    //phases
    flecs::entity load_events_phase;
    {
      const ::engine::Window* window_module = world.get<::engine::Window>();
      assert(window_module);
      load_events_phase = window_module->load_events_phase;
    }


    //systems
    world.system<const window::MainWindowInit>("system::InitSystem")
      .term_at(1).singleton()
      .iter(detail::InitSystem);
    
    world.system<window::MainWindow, const MainWindowSFML, WindowBackendSfml>("system::EventPoll")
      .kind(load_events_phase)
      .term_at(1).singleton()
      .term_at(2).singleton()
      .term_at(3).singleton()
      .iter(detail::PollEvents);

  }
} //namespace engine::window_backend_sfml::internal