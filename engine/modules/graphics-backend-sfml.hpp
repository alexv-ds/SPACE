#pragma once
#include <memory>
#include <flecs.h>
#include <SFML/Graphics/RenderTarget.hpp>

namespace engine {

struct GraphicsBackendSFML {
  GraphicsBackendSFML(flecs::world&);
};

} //namespace engine


namespace engine::graphics_backend_sfml {

struct RenderTarget {
  std::shared_ptr<sf::RenderTarget> target;
};

} //namespace engine::graphics_backend_sfml