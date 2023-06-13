#include <engine/graphics/canvas.hpp>
#include <engine/graphics/color.hpp>

#include "graphics.hpp"

engine::Graphics::Graphics(flecs::world& world) {
  using namespace graphics;

  world.module<Graphics>("graphics");

  //components
  world.component<Color>()
    .member<decltype(Color::r)>("r")
    .member<decltype(Color::g)>("g")
    .member<decltype(Color::b)>("b");

  world.component<Transparency>()
    .member<decltype(Transparency::a)>("a");

  world.component<Canvas>();
}