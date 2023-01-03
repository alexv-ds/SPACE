#include <type_traits>
#include <unordered_map>
#include <spdlog/spdlog.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "window-backend-sfml.hpp"
#include "window.hpp"


namespace engine::window_backend_sfml::internal {

/////////////////////////////////////
///////////ENUM MAPPINGS/////////////
/////////////////////////////////////

const std::unordered_map<sf::Keyboard::Key, window::Key> key_mapping = {
  {sf::Keyboard::A, window::Key::A},
  {sf::Keyboard::B, window::Key::B},
  {sf::Keyboard::C, window::Key::C},
  {sf::Keyboard::D, window::Key::D},
  {sf::Keyboard::E, window::Key::E},
  {sf::Keyboard::F, window::Key::F},
  {sf::Keyboard::G, window::Key::G},
  {sf::Keyboard::H, window::Key::H},
  {sf::Keyboard::I, window::Key::I},
  {sf::Keyboard::J, window::Key::J},
  {sf::Keyboard::K, window::Key::K},
  {sf::Keyboard::L, window::Key::L},
  {sf::Keyboard::M, window::Key::M},
  {sf::Keyboard::N, window::Key::N},
  {sf::Keyboard::O, window::Key::O},
  {sf::Keyboard::P, window::Key::P},
  {sf::Keyboard::Q, window::Key::Q},
  {sf::Keyboard::R, window::Key::R},
  {sf::Keyboard::S, window::Key::S},
  {sf::Keyboard::T, window::Key::T},
  {sf::Keyboard::U, window::Key::U},
  {sf::Keyboard::V, window::Key::V},
  {sf::Keyboard::W, window::Key::W},
  {sf::Keyboard::X, window::Key::X},
  {sf::Keyboard::Y, window::Key::Y},
  {sf::Keyboard::Z, window::Key::Z},
  {sf::Keyboard::Num0, window::Key::Num0},
  {sf::Keyboard::Num1, window::Key::Num1},
  {sf::Keyboard::Num2, window::Key::Num2},
  {sf::Keyboard::Num3, window::Key::Num3},
  {sf::Keyboard::Num4, window::Key::Num4},
  {sf::Keyboard::Num5, window::Key::Num5},
  {sf::Keyboard::Num6, window::Key::Num6},
  {sf::Keyboard::Num7, window::Key::Num7},
  {sf::Keyboard::Num8, window::Key::Num8},
  {sf::Keyboard::Num9, window::Key::Num9},
  {sf::Keyboard::Escape, window::Key::Escape},
  {sf::Keyboard::LControl, window::Key::LControl},
  {sf::Keyboard::LShift, window::Key::LShift},
  {sf::Keyboard::LAlt, window::Key::LAlt},
  {sf::Keyboard::LSystem, window::Key::LSystem},
  {sf::Keyboard::RControl, window::Key::RControl},
  {sf::Keyboard::RShift, window::Key::RShift},
  {sf::Keyboard::RAlt, window::Key::RAlt},
  {sf::Keyboard::RSystem, window::Key::RSystem},
  {sf::Keyboard::Menu, window::Key::Menu},
  {sf::Keyboard::LBracket, window::Key::LBracket},
  {sf::Keyboard::RBracket, window::Key::RBracket},
  {sf::Keyboard::Semicolon, window::Key::Semicolon},
  {sf::Keyboard::Comma, window::Key::Comma},
  {sf::Keyboard::Period, window::Key::Period},
  {sf::Keyboard::Quote, window::Key::Quote},
  {sf::Keyboard::Slash, window::Key::Slash},
  {sf::Keyboard::Backslash, window::Key::Backslash},
  {sf::Keyboard::Tilde, window::Key::Tilde},
  {sf::Keyboard::Equal, window::Key::Equal},
  {sf::Keyboard::Hyphen, window::Key::Hyphen},
  {sf::Keyboard::Space, window::Key::Space},
  {sf::Keyboard::Enter, window::Key::Enter},
  {sf::Keyboard::Backspace, window::Key::Backspace},
  {sf::Keyboard::Tab, window::Key::Tab},
  {sf::Keyboard::PageUp, window::Key::PageUp},
  {sf::Keyboard::PageDown, window::Key::PageDown},
  {sf::Keyboard::End, window::Key::End},
  {sf::Keyboard::Home, window::Key::Home},
  {sf::Keyboard::Insert, window::Key::Insert},
  {sf::Keyboard::Delete, window::Key::Delete},
  {sf::Keyboard::Add, window::Key::Add},
  {sf::Keyboard::Subtract, window::Key::Subtract},
  {sf::Keyboard::Multiply, window::Key::Multiply},
  {sf::Keyboard::Divide, window::Key::Divide},
  {sf::Keyboard::Left, window::Key::Left},
  {sf::Keyboard::Right, window::Key::Right},
  {sf::Keyboard::Up, window::Key::Up},
  {sf::Keyboard::Down, window::Key::Down},
  {sf::Keyboard::Numpad0, window::Key::Numpad0},
  {sf::Keyboard::Numpad1, window::Key::Numpad1},
  {sf::Keyboard::Numpad2, window::Key::Numpad2},
  {sf::Keyboard::Numpad3, window::Key::Numpad3},
  {sf::Keyboard::Numpad4, window::Key::Numpad4},
  {sf::Keyboard::Numpad5, window::Key::Numpad5},
  {sf::Keyboard::Numpad6, window::Key::Numpad6},
  {sf::Keyboard::Numpad7, window::Key::Numpad7},
  {sf::Keyboard::Numpad8, window::Key::Numpad8},
  {sf::Keyboard::Numpad9, window::Key::Numpad9},
  {sf::Keyboard::F1, window::Key::F1},
  {sf::Keyboard::F2, window::Key::F2},
  {sf::Keyboard::F3, window::Key::F3},
  {sf::Keyboard::F4, window::Key::F4},
  {sf::Keyboard::F5, window::Key::F5},
  {sf::Keyboard::F6, window::Key::F6},
  {sf::Keyboard::F7, window::Key::F7},
  {sf::Keyboard::F8, window::Key::F8},
  {sf::Keyboard::F9, window::Key::F9},
  {sf::Keyboard::F10, window::Key::F10},
  {sf::Keyboard::F11, window::Key::F11},
  {sf::Keyboard::F12, window::Key::F12},
  {sf::Keyboard::F13, window::Key::F13},
  {sf::Keyboard::F14, window::Key::F14},
  {sf::Keyboard::F15, window::Key::F15},
  {sf::Keyboard::Pause, window::Key::Pause}
};

const std::unordered_map<sf::Mouse::Button, window::MouseButton> mouse_mapping = {
  {sf::Mouse::Left, window::MouseButton::Left},
  {sf::Mouse::Right, window::MouseButton::Right},
  {sf::Mouse::Middle, window::MouseButton::Middle},
  {sf::Mouse::XButton1, window::MouseButton::XButton1},
  {sf::Mouse::XButton2, window::MouseButton::XButton2}
};

/////////////////////////////////////
/////////////SYSTEMS/////////////////
/////////////////////////////////////

void InitSystem(flecs::iter it, const window::MainWindowInit* init) {
  sf::VideoMode video_mode({init->width, init->height});

  //Проверки на этапе компиляции на совместимость sf::Style и window::Style
  //Ибо window::Style были скопированы с sf::Style, но на будущее, если внезапно что-то поменяется
  //тут будет ошибка и будет сразу ясно о несовместимости
  static_assert(sf::Style::Close == static_cast<std::uint32_t>(window::Style::Close));
  static_assert(sf::Style::Default == static_cast<std::uint32_t>(window::Style::Default));
  static_assert(sf::Style::Fullscreen == static_cast<std::uint32_t>(window::Style::Fullscreen));
  static_assert(sf::Style::None == static_cast<std::uint32_t>(window::Style::None));
  static_assert(sf::Style::Resize == static_cast<std::uint32_t>(window::Style::Resize));
  static_assert(sf::Style::Titlebar == static_cast<std::uint32_t>(window::Style::Titlebar));
  std::uint32_t style = static_cast<std::uint32_t>(init->style);

  sf::ContextSettings settings;
  settings.majorVersion = 4;
  settings.minorVersion = 6;
  settings.attributeFlags = sf::ContextSettings::Core | sf::ContextSettings::Debug;

  std::shared_ptr sfml_window = std::make_shared<sf::Window>();
  sfml_window->create(video_mode, init->title, style, settings);
  sf::ContextSettings actual_settings = sfml_window->getSettings();
  it.world().set<MainWindowSFML>({std::move(sfml_window)});
  it.world().set<window::MainWindow>({.width=init->width, .height=init->height});
  it.world().remove<window::MainWindowInit>();

  //проверяем запрашиваемый контекст и фактически созданный
  if (settings.depthBits != actual_settings.depthBits) {
    SPDLOG_WARN("Запрашиваемое значение depthBits ({}) отличается от фактически созданного ({})", settings.depthBits, actual_settings.depthBits);
  }
  if (settings.stencilBits != actual_settings.stencilBits) {
    SPDLOG_WARN("Запрашиваемое значение stencilBits ({}) отличается от фактически созданного ({})", settings.stencilBits, actual_settings.stencilBits);
  }
  if (settings.antialiasingLevel != actual_settings.antialiasingLevel) {
    SPDLOG_WARN("Запрашиваемое значение antialiasingLevel ({}) отличается от фактически созданного ({})", settings.antialiasingLevel, actual_settings.antialiasingLevel);
  }
  if (settings.majorVersion != actual_settings.majorVersion) {
    SPDLOG_WARN("Запрашиваемое значение majorVersion ({}) отличается от фактически созданного ({})", settings.majorVersion, actual_settings.majorVersion);
  }
  if (settings.minorVersion != actual_settings.minorVersion) {
    SPDLOG_WARN("Запрашиваемое значение minorVersion ({}) отличается от фактически созданного ({})", settings.minorVersion, actual_settings.minorVersion);
  }
  if (settings.attributeFlags != actual_settings.attributeFlags) {
    SPDLOG_WARN("Запрашиваемое значение attributeFlags ({}) отличается от фактически созданного ({})", settings.attributeFlags, actual_settings.attributeFlags);
  }
  if (settings.sRgbCapable != actual_settings.sRgbCapable) {
    SPDLOG_WARN("Запрашиваемое значение sRgbCapable ({}) отличается от фактически созданного ({})", settings.sRgbCapable, actual_settings.sRgbCapable);
  }
}

template <class T>
static flecs::entity create_event_entity(flecs::world& world, std::size_t index, T comp) {
  flecs::entity event_entity = world.entity();
  event_entity.child_of(world.entity<window::MainWindow>());
  event_entity.set<window::Event>({.index=index});
  if constexpr (std::is_empty_v<T>) {
    event_entity.add<T>();
  } else {
    event_entity.set<T>(comp);
  }
  return event_entity;
}

void EventPoll(flecs::iter it, const MainWindowSFML* sfml_window) {
  if(!sfml_window->window || !sfml_window->window->isOpen()) {
    SPDLOG_ERROR("Cannot poll SFML Window events: window does not exist");
    return;
  }
  flecs::world world = it.world();
  thread_local std::size_t event_index = 0;
  sf::Event event;
  while (sfml_window->window->pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed: {
        create_event_entity(world, ++event_index, window::event::Closed{});
        break;
      }
      case sf::Event::Resized: {
        create_event_entity(world, ++event_index, window::event::Resized{
          .width = event.size.width,
          .height = event.size.height
        });
        break;
      }
      case sf::Event::LostFocus: {
        create_event_entity(world, ++event_index, window::event::LostFocus{});
        break;
      }
      case sf::Event::GainedFocus: {
        create_event_entity(world, ++event_index, window::event::GainedFocus{});
        break;
      }
      case sf::Event::TextEntered: {
        create_event_entity(world, ++event_index, window::event::TextEntered{
          .unicode = event.text.unicode
        });
        break;
      }
      case sf::Event::KeyPressed: {
        if (auto it = key_mapping.find(event.key.code); it != key_mapping.end()) {
          create_event_entity(world, ++event_index, window::event::KeyPressed{
            .code = it->second,
            .alt = event.key.alt,
            .control = event.key.control,
            .shift = event.key.shift,
            .system = event.key.system,
          });
        } else {
          SPDLOG_WARN(
            "Unknown key code in window event: {}", 
            static_cast<std::underlying_type_t<sf::Keyboard::Key>>(event.key.code)
          );
        }
        break;
      }
      case sf::Event::KeyReleased: {
        if (auto it = key_mapping.find(event.key.code); it != key_mapping.end()) {
          create_event_entity(world, ++event_index, window::event::KeyReleased{
            .code = it->second
          });
        } else {
          SPDLOG_WARN(
            "Unknown key code in window event: {}", 
            static_cast<std::underlying_type_t<sf::Keyboard::Key>>(event.key.code)
          );
        }
        break;
      }
      case sf::Event::MouseWheelScrolled: {
        window::MouseWheel wheel;
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
          wheel = window::MouseWheel::Vertical;
        } else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
          wheel = window::MouseWheel::Horizontal;
        } else {
          SPDLOG_WARN("Unknown mouse wheel in window event");
          break;
        }
        create_event_entity(world, ++event_index, window::event::MouseWheelScrolled{
          .wheel = wheel,
          .delta = event.mouseWheelScroll.delta,
          .x = event.mouseWheelScroll.x,
          .y = event.mouseWheelScroll.y
        });
        break;
      }
      case sf::Event::MouseButtonPressed: {
        if (auto it = mouse_mapping.find(event.mouseButton.button); it != mouse_mapping.end()) {
          create_event_entity(world, ++event_index, window::event::MouseButtonPressed{
            .button = it->second,
            .x = event.mouseButton.x,
            .y = event.mouseButton.y
          });
        } else {
          SPDLOG_WARN(
            "Unknown mouse button code in window event: {}", 
            static_cast<std::underlying_type_t<sf::Mouse::Button>>(event.mouseButton.button)
          );
        }
        break;
      }
      case sf::Event::MouseButtonReleased: {
        if (auto it = mouse_mapping.find(event.mouseButton.button); it != mouse_mapping.end()) {
          create_event_entity(world, ++event_index, window::event::MouseButtonReleased{
            .button = it->second,
            .x = event.mouseButton.x,
            .y = event.mouseButton.y
          });
        } else {
          SPDLOG_WARN(
            "Unknown mouse button code in window event: {}", 
            static_cast<std::underlying_type_t<sf::Mouse::Button>>(event.mouseButton.button)
          );
        }
        break;
      }
      case sf::Event::MouseMoved: {
        create_event_entity(world, ++event_index, window::event::MouseMoved{
          .x = event.mouseMove.x,
          .y = event.mouseMove.y
        });
        break;
      }
      case sf::Event::MouseEntered: {
        create_event_entity(world, ++event_index, window::event::MouseEntered{});
        break;
      }
      case sf::Event::MouseLeft: {
        create_event_entity(world, ++event_index, window::event::MouseLeft{});
        break;
      }
    } //end of switch
  } //end of while
}

void WindowClear(flecs::iter it, const MainWindowSFML* sfml_window) {
  if(!sfml_window->window || !sfml_window->window->isOpen()) {
    SPDLOG_ERROR("Cannot clear() SFML Window: window does not exist");
    return;
  }
  //sfml_window->window->clear();
};
void WindowDisplay(flecs::iter it, const MainWindowSFML* sfml_window) {
  if(!sfml_window->window || !sfml_window->window->isOpen()) {
    SPDLOG_ERROR("Cannot display() SFML Window: window does not exist");
    return;
  }
  sfml_window->window->display();
};


} //namespace engine::window_backend_sfml::internal

namespace engine {
  using namespace window_backend_sfml;

  WindowBackendSfml::WindowBackendSfml(flecs::world& world) {
    world.import<Window>();
    world.module<WindowBackendSfml>("window_backend_sfml");

    world.system<const window::MainWindowInit>("system::InitSystem")
      .no_readonly()
      .term_at(1).singleton()
      .iter(internal::InitSystem);
    
    world.system<const MainWindowSFML>("system::EventPoll")
      .no_readonly()
      .kind(flecs::OnLoad)
      .term_at(1).singleton()
      .term<window::MainWindow>().singleton()
      .iter(internal::EventPoll);
    
    world.system<const MainWindowSFML>("system::WindowDisplay")
      .no_readonly()
      .kind(flecs::PostFrame)
      .term_at(1).singleton()
      .term<window::MainWindow>().singleton()
      .iter(internal::WindowDisplay);
  }
} //namespace engine::window_backend_sfml::internal