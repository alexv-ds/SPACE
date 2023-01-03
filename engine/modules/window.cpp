#include <type_traits>
#include "window.hpp"
#include <spdlog/spdlog.h>

namespace engine::window::detail {
  void CleanupEvents(flecs::entity e) {
    e.destruct();
  }  
};


namespace engine {
  using namespace window;

  Window::Window(flecs::world& world) {
    world.import<flecs::units>();
    world.module<Window>("window");

    static_assert(std::is_same_v<std::underlying_type_t<Style>, std::uint32_t>);
    world.component<Style>("Style")
      .bit("None", static_cast<std::uint32_t>(Style::None))
      .bit("Titlebar", static_cast<std::uint32_t>(Style::Titlebar))
      .bit("Resize", static_cast<std::uint32_t>(Style::Resize))
      .bit("Close", static_cast<std::uint32_t>(Style::Close))
      .bit("Fullscreen", static_cast<std::uint32_t>(Style::Fullscreen))
      .bit("Default", static_cast<std::uint32_t>(Style::Default));

    static_assert(std::is_same_v<std::underlying_type_t<Key>, std::int32_t>);
    world.component<Key>("Key")
      .constant("A", static_cast<std::int32_t>(Key::A))
      .constant("B", static_cast<std::int32_t>(Key::B))
      .constant("C", static_cast<std::int32_t>(Key::C))
      .constant("D", static_cast<std::int32_t>(Key::D))
      .constant("E", static_cast<std::int32_t>(Key::E))
      .constant("F", static_cast<std::int32_t>(Key::F))
      .constant("G", static_cast<std::int32_t>(Key::G))
      .constant("H", static_cast<std::int32_t>(Key::H))
      .constant("I", static_cast<std::int32_t>(Key::I))
      .constant("J", static_cast<std::int32_t>(Key::J))
      .constant("K", static_cast<std::int32_t>(Key::K))
      .constant("L", static_cast<std::int32_t>(Key::L))
      .constant("M", static_cast<std::int32_t>(Key::M))
      .constant("N", static_cast<std::int32_t>(Key::N))
      .constant("O", static_cast<std::int32_t>(Key::O))
      .constant("P", static_cast<std::int32_t>(Key::P))
      .constant("Q", static_cast<std::int32_t>(Key::Q))
      .constant("R", static_cast<std::int32_t>(Key::R))
      .constant("S", static_cast<std::int32_t>(Key::S))
      .constant("T", static_cast<std::int32_t>(Key::T))
      .constant("U", static_cast<std::int32_t>(Key::U))
      .constant("V", static_cast<std::int32_t>(Key::V))
      .constant("W", static_cast<std::int32_t>(Key::W))
      .constant("X", static_cast<std::int32_t>(Key::X))
      .constant("Y", static_cast<std::int32_t>(Key::Y))
      .constant("Z", static_cast<std::int32_t>(Key::Z))
      .constant("Num0", static_cast<std::int32_t>(Key::Num0))
      .constant("Num1", static_cast<std::int32_t>(Key::Num1))
      .constant("Num2", static_cast<std::int32_t>(Key::Num2))
      .constant("Num3", static_cast<std::int32_t>(Key::Num3))
      .constant("Num4", static_cast<std::int32_t>(Key::Num4))
      .constant("Num5", static_cast<std::int32_t>(Key::Num5))
      .constant("Num6", static_cast<std::int32_t>(Key::Num6))
      .constant("Num7", static_cast<std::int32_t>(Key::Num7))
      .constant("Num8", static_cast<std::int32_t>(Key::Num8))
      .constant("Num9", static_cast<std::int32_t>(Key::Num9))
      .constant("Escape", static_cast<std::int32_t>(Key::Escape))
      .constant("LControl", static_cast<std::int32_t>(Key::LControl))
      .constant("LShift", static_cast<std::int32_t>(Key::LShift))
      .constant("LAlt", static_cast<std::int32_t>(Key::LAlt))
      .constant("LSystem", static_cast<std::int32_t>(Key::LSystem))
      .constant("RControl", static_cast<std::int32_t>(Key::RControl))
      .constant("RShift", static_cast<std::int32_t>(Key::RShift))
      .constant("RAlt", static_cast<std::int32_t>(Key::RAlt))
      .constant("RSystem", static_cast<std::int32_t>(Key::RSystem))
      .constant("Menu", static_cast<std::int32_t>(Key::Menu))
      .constant("LBracket", static_cast<std::int32_t>(Key::LBracket))
      .constant("RBracket", static_cast<std::int32_t>(Key::RBracket))
      .constant("Semicolon", static_cast<std::int32_t>(Key::Semicolon))
      .constant("Comma", static_cast<std::int32_t>(Key::Comma))
      .constant("Period", static_cast<std::int32_t>(Key::Period))
      .constant("Quote", static_cast<std::int32_t>(Key::Quote))
      .constant("Slash", static_cast<std::int32_t>(Key::Slash))
      .constant("Backslash", static_cast<std::int32_t>(Key::Backslash))
      .constant("Tilde", static_cast<std::int32_t>(Key::Tilde))
      .constant("Equal", static_cast<std::int32_t>(Key::Equal))
      .constant("Hyphen", static_cast<std::int32_t>(Key::Hyphen))
      .constant("Space", static_cast<std::int32_t>(Key::Space))
      .constant("Enter", static_cast<std::int32_t>(Key::Enter))
      .constant("Backspace", static_cast<std::int32_t>(Key::Backspace))
      .constant("Tab", static_cast<std::int32_t>(Key::Tab))
      .constant("PageUp", static_cast<std::int32_t>(Key::PageUp))
      .constant("PageDown", static_cast<std::int32_t>(Key::PageDown))
      .constant("End", static_cast<std::int32_t>(Key::End))
      .constant("Home", static_cast<std::int32_t>(Key::Home))
      .constant("Insert", static_cast<std::int32_t>(Key::Insert))
      .constant("Delete", static_cast<std::int32_t>(Key::Delete))
      .constant("Add", static_cast<std::int32_t>(Key::Add))
      .constant("Subtract", static_cast<std::int32_t>(Key::Subtract))
      .constant("Multiply", static_cast<std::int32_t>(Key::Multiply))
      .constant("Divide", static_cast<std::int32_t>(Key::Divide))
      .constant("Left", static_cast<std::int32_t>(Key::Left))
      .constant("Right", static_cast<std::int32_t>(Key::Right))
      .constant("Up", static_cast<std::int32_t>(Key::Up))
      .constant("Down", static_cast<std::int32_t>(Key::Down))
      .constant("Numpad0", static_cast<std::int32_t>(Key::Numpad0))
      .constant("Numpad1", static_cast<std::int32_t>(Key::Numpad1))
      .constant("Numpad2", static_cast<std::int32_t>(Key::Numpad2))
      .constant("Numpad3", static_cast<std::int32_t>(Key::Numpad3))
      .constant("Numpad4", static_cast<std::int32_t>(Key::Numpad4))
      .constant("Numpad5", static_cast<std::int32_t>(Key::Numpad5))
      .constant("Numpad6", static_cast<std::int32_t>(Key::Numpad6))
      .constant("Numpad7", static_cast<std::int32_t>(Key::Numpad7))
      .constant("Numpad8", static_cast<std::int32_t>(Key::Numpad8))
      .constant("Numpad9", static_cast<std::int32_t>(Key::Numpad9))
      .constant("F1", static_cast<std::int32_t>(Key::F1))
      .constant("F2", static_cast<std::int32_t>(Key::F2))
      .constant("F3", static_cast<std::int32_t>(Key::F3))
      .constant("F4", static_cast<std::int32_t>(Key::F4))
      .constant("F5", static_cast<std::int32_t>(Key::F5))
      .constant("F6", static_cast<std::int32_t>(Key::F6))
      .constant("F7", static_cast<std::int32_t>(Key::F7))
      .constant("F8", static_cast<std::int32_t>(Key::F8))
      .constant("F9", static_cast<std::int32_t>(Key::F9))
      .constant("F10", static_cast<std::int32_t>(Key::F10))
      .constant("F11", static_cast<std::int32_t>(Key::F11))
      .constant("F12", static_cast<std::int32_t>(Key::F12))
      .constant("F13", static_cast<std::int32_t>(Key::F13))
      .constant("F14", static_cast<std::int32_t>(Key::F14))
      .constant("F15", static_cast<std::int32_t>(Key::F15))
      .constant("Pause", static_cast<std::int32_t>(Key::Pause));

    static_assert(std::is_same_v<std::underlying_type_t<MouseWheel>, std::int32_t>);
    world.component<MouseWheel>("MouseWheel")
      .constant("Vertical", static_cast<std::int32_t>(MouseWheel::Vertical))
      .constant("Horizontal", static_cast<std::int32_t>(MouseWheel::Horizontal));

    static_assert(std::is_same_v<std::underlying_type_t<MouseButton>, std::int32_t>);
    world.component<MouseButton>("MouseButton")
      .constant("Left", static_cast<std::int32_t>(MouseButton::Left))
      .constant("Right", static_cast<std::int32_t>(MouseButton::Right))
      .constant("Middle", static_cast<std::int32_t>(MouseButton::Middle))
      .constant("XButton1", static_cast<std::int32_t>(MouseButton::XButton1))
      .constant("XButton2", static_cast<std::int32_t>(MouseButton::XButton2));
    
    world.component<MainWindowInit>();
    world.component<MainWindow>()
      .member<decltype(MainWindow::width), flecs::units::length::Pixels>("width")
      .member<decltype(MainWindow::height), flecs::units::length::Pixels>("height");
    world.component<Event>()
      .member<decltype(Event::index)>("index");
    
    //events
    world.component<event::Closed>("event::Closed");
    world.component<event::Resized>("event::Resized")
      .member<decltype(event::Resized::width)>("width")
      .member<decltype(event::Resized::height)>("height");
    world.component<event::LostFocus>("event::LostFocus");
    world.component<event::GainedFocus>("event::GainedFocus");
    world.component<event::TextEntered>("event::TextEntered")
      .member<decltype(event::TextEntered::unicode)>("unicode");
    world.component<event::KeyPressed>("event::KeyPressed")
      .member<decltype(event::KeyPressed::code)>("code")
      .member<decltype(event::KeyPressed::alt)>("alt")
      .member<decltype(event::KeyPressed::control)>("control")
      .member<decltype(event::KeyPressed::shift)>("shift")
      .member<decltype(event::KeyPressed::system)>("system");
    world.component<event::KeyReleased>("event::KeyReleased")
      .member<decltype(event::KeyPressed::code)>("code");
    world.component<event::MouseWheelScrolled>("event::MouseWheelScrolled")
      .member<decltype(event::MouseWheelScrolled::wheel)>("wheel")
      .member<decltype(event::MouseWheelScrolled::delta)>("delta")
      .member<decltype(event::MouseWheelScrolled::x)>("x")
      .member<decltype(event::MouseWheelScrolled::y)>("y");
    world.component<event::MouseButtonPressed>("event::MouseButtonPressed")
      .member<decltype(event::MouseButtonPressed::button)>("button")
      .member<decltype(event::MouseButtonPressed::x)>("x")
      .member<decltype(event::MouseButtonPressed::y)>("y");
    world.component<event::MouseButtonReleased>("event::MouseButtonReleased")
      .member<decltype(event::MouseButtonReleased::button)>("button")
      .member<decltype(event::MouseButtonReleased::x)>("x")
      .member<decltype(event::MouseButtonReleased::y)>("y");
    world.component<event::MouseMoved>("event::MouseMoved")
      .member<decltype(event::MouseMoved::x)>("x")
      .member<decltype(event::MouseMoved::y)>("y");
    world.component<event::MouseEntered>("event::MouseEntered");
    world.component<event::MouseLeft>("event::MouseLeft");

    //systems

    world.system("system::CleanupEvents")
      .kind(flecs::PostFrame)
      .term<MainWindow>().singleton()
      .term<Event>()
      .term(flecs::ChildOf, world.entity<window::MainWindow>())
      .each(detail::CleanupEvents);
  };
}


