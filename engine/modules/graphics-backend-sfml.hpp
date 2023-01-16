#pragma once
#include <memory>
#include <flecs.h>
#include <SFML/Graphics.hpp>

namespace engine {

struct GraphicsBackendSFML {
  GraphicsBackendSFML(flecs::world&);
};

} //namespace engine


namespace engine::graphics_backend_sfml {

struct RenderTarget {
  std::shared_ptr<sf::RenderTarget> target;
};

struct Square {
  sf::RectangleShape rect;
};

struct Circle {
  sf::CircleShape circle;
};

struct Rectangle {
  sf::RectangleShape rect;
};

} //namespace engine::graphics_backend_sfml