#pragma once
#include <memory>
#include <flecs.h>
#include <SFML/Graphics/RenderWindow.hpp>

namespace engine {

struct ImguiBackendSfml {
  ImguiBackendSfml(flecs::world&);
};

} //namespace engine

namespace engine::imgui_backend_sfml {

struct Context {

  Context();
  ~Context();

  class ContextLock;
  std::shared_ptr<ContextLock> lock;
};



} //namespace engine::imgui_backend_sfml


