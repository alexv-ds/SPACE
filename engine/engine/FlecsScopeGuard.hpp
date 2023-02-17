#pragma once
#include <flecs.h>

namespace engine {

class FlecsScopeGuard {
public:
  FlecsScopeGuard(const engine::FlecsScopeGuard&) = delete;
  FlecsScopeGuard(const engine::FlecsScopeGuard&&) = delete;

  inline FlecsScopeGuard(flecs::entity new_scope):
      prev_scope(new_scope.world().set_scope(new_scope))
  {}

  inline ~FlecsScopeGuard() {
    restore();
  }

  inline void restore() {
    if (this->prev_scope != flecs::entity::null()) {
      this->prev_scope.world().set_scope(this->prev_scope);
      this->prev_scope = flecs::entity::null();
    }
  }

private:
  flecs::entity prev_scope;
};

} //namespace engine

