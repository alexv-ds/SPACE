#pragma once
#include <flecs.h>

namespace engine {

class FlecsScopeGuard {
public:
  FlecsScopeGuard(const engine::FlecsScopeGuard&) = delete;
  FlecsScopeGuard(const engine::FlecsScopeGuard&&) = delete;

  inline FlecsScopeGuard(flecs::entity new_scope):
      prev_scope(new_scope.world().set_scope(new_scope)),
      world(new_scope.world())
  {}

  inline ~FlecsScopeGuard() {
    restore();
  }

  inline void restore() {
    if (!this->restored) {
      this->world.set_scope(this->prev_scope);
      this->prev_scope = flecs::entity::null();
    }
  }

private:
  bool restored = false;
  flecs::entity prev_scope;
  flecs::world world;
};

} //namespace engine

