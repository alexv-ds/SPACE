#pragma once
#include <vector>
#include "Event.hpp"
#include "../noncopyable.hpp"

namespace engine::window {

class FrameEventsStorage {
public:
  template <class T>
  inline void push(T event_type);

private:
  std::vector<Event> events;
};


//inline methods
template <class T>
inline void FrameEventsStorage::push(T event_type) {
  this->events.emplace_back(event_type);
}

}; //namespace engine::window