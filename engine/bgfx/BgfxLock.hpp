#pragma once
#include <SFML/Window/WindowBase.hpp>

namespace engine::bgfx {

class BgfxLock {
public:
  inline BgfxLock(std::shared_ptr<sf::WindowBase> window): window(std::move(window)) {}
  ~BgfxLock();
private:
  std::shared_ptr<sf::WindowBase> window;
};

} //namespace engine::graphics_backend_bgfx