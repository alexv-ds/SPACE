#pragma once
#include <vector>
#include "Event.hpp"
#include "../engine/noncopyable.hpp"

namespace engine::window {

class FrameEventsStorage {
public:
  template <class T>
  inline void push(T event_type);

  template <class T>
  inline void push();

  inline void clear();
  
  template <class T>
  void iterate(T cb_func);

  template <class T>
  void iterate_all(T cb_func);

  inline std::size_t raw_size() const noexcept;
private:
  std::vector<Event> events;
};

//impl
template <class T>
inline void FrameEventsStorage::push(T event_type) {
  this->events.emplace_back(std::move(event_type));
}

template <class T>
inline void FrameEventsStorage::push() {
  this->events.emplace_back(Event(T()));
}

inline void FrameEventsStorage::clear() {
  this->events.clear();
}

template <class T>
inline void FrameEventsStorage::iterate(T cb_func) {
  for (Event& event : this->events) {
    if (!event.is_discarded()) {
      cb_func(event);
    }
  }
}

template <class T>
void FrameEventsStorage::iterate_all(T cb_func) {
  for (Event& event : this->events) {
    cb_func(event);
  }
}

inline std::size_t FrameEventsStorage::raw_size() const noexcept {
  return this->events.size();
}

}; //namespace engine::window