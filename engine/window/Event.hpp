#pragma once
#include <cstdint>
#include <variant>
#include <type_traits>
#include "Keyboard.hpp"
#include "Mouse.hpp"

namespace engine::window {

  namespace event_type {

    struct Closed {};

    struct LostFocus {};

    struct GainedFocus {};

    struct MouseEntered {};
    
    struct MouseLeft {};

    struct Resized {
      std::uint32_t width; //in pixels
      std::uint32_t height;
    };

    struct TextEntered {
      std::uint32_t unicode; //!< UTF-32 Unicode value of the character
    };

    struct KeyPressed {
      ::engine::window::Key key;
      ::engine::window::Scancode scancode; //!< Physical code of the key that has been pressed
      bool alt;
      bool control;
      bool shift;
      bool system; 
    };

    struct KeyReleased {
      ::engine::window::Key key;
      ::engine::window::Scancode scancode;
      bool alt;
      bool control;
      bool shift;
      bool system; 
    };

    struct MouseWheelScrolled {
      ::engine::window::MouseWheel wheel; //!< Which wheel (for mice with multiple ones)
      float delta; //!< Wheel offset (positive is up/left, negative is down/right). High-precision mice may use non-integral offsets.
      std::int32_t x; //!< X position of the mouse pointer, relative to the left of the owner window
      std::int32_t y; //!< Y position of the mouse pointer, relative to the top of the owner window
    };

    struct MouseButtonPressed {
      ::engine::window::MouseButton button;
      std::int32_t x;  //!< X position of the mouse pointer, relative to the left of the owner window
      std::int32_t y;  //!< Y position of the mouse pointer, relative to the top of the owner window
    };

    struct MouseButtonReleased {
      ::engine::window::MouseButton button;
      std::int32_t x;  //!< X position of the mouse pointer, relative to the left of the owner window
      std::int32_t y;  //!< Y position of the mouse pointer, relative to the top of the owner window
    };

    struct MouseMoved {
      std::int32_t x; //!< X position of the mouse pointer, relative to the left of the owner window
      std::int32_t y; //!< Y position of the mouse pointer, relative to the top of the owner window
    };
  } //namespace EventType;

class Event {
public:
  template <class T>
  inline Event(T event_type) noexcept(std::is_nothrow_convertible_v<VariantType>);

  //Check is event has given type
  template <class T>
  inline bool is_event() const noexcept;

  template <class T>
  inline const T& get() const;

  template <class T>
  inline const T* try_get() const noexcept;

  inline void discard() noexcept;
  inline bool is_discarded() const noexcept;

private:
  //internal
  using VariantType = std::variant<event_type::Closed,             event_type::Resized, 
                                   event_type::GainedFocus,        event_type::TextEntered,
                                   event_type::KeyReleased,        event_type::MouseWheelScrolled,
                                   event_type::MouseButtonPressed, event_type::MouseButtonReleased,
                                   event_type::MouseMoved,         event_type::MouseEntered,
                                   event_type::MouseLeft,          event_type::LostFocus,
                                   event_type::KeyPressed>;

  VariantType event;
  bool discarded = false;
};

//inline methods
template <class T>
inline Event::Event(T event_type) noexcept(std::is_nothrow_convertible_v<VariantType>): event(event_type) {}

template <class T>
inline bool Event::is_event() const noexcept {
  return std::holds_alternative<T>(this->event);
}

template <class T>
inline const T& Event::get() const {
  return std::get<T>(this->event);
}

template <class T>
inline const T* Event::try_get() const noexcept {
  return std::get_if<T>();
}

inline void Event::discard() noexcept {
  this->discarded = true;
}

inline bool Event::is_discarded() const noexcept {
  return this->discarded;
}

} //namespace engine::window