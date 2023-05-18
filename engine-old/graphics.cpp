#include <cmath>
#include <spdlog/spdlog.h>
#include "graphics.hpp"
#include "glm-reflection.hpp"
#include "window.hpp"
#include "geometry.hpp"

namespace engine::graphics::detail {

void MainCameraSizeController(flecs::entity e, const MainWindowCamera& main_camera, geometry::Rectangle& rect) {
  const window::MainWindow* main_window = e.world().get<window::MainWindow>();
  float theoretical_tile_size;
  if (main_window->height < main_window->width) {
    theoretical_tile_size = main_window->height / main_camera.camera_size.y;
  } else {
    theoretical_tile_size = main_window->width / main_camera.camera_size.x;
  }
  float tile_size = std::ceil(theoretical_tile_size);
  rect.height = static_cast<float>(main_window->height) / tile_size;
  rect.width = static_cast<float>(main_window->width) / tile_size;
}

} //namespace engine::graphics::detail

namespace engine {
using namespace graphics;

Graphics::Graphics(flecs::world& world) {
  world.import<GlmReflection>();
  world.import<Window>();
  world.import<Geometry>();
  world.module<Graphics>("graphics");

  world.component<Color>()
    .member<decltype(Color::r)>("r")
    .member<decltype(Color::g)>("g")
    .member<decltype(Color::b)>("b");

  world.component<Transparency>()
    .member<decltype(Transparency::a)>("a");

  world.component<Camera>();

  world.component<MainWindowCamera>()
    .member<decltype(MainWindowCamera::camera_size)>("camera_size");

  world.component<RenderedBy>()
    .add(flecs::Traversable);


  //systems
  world.system<const MainWindowCamera, geometry::Rectangle>("system::MainCameraSizeController")
    .with<window::MainWindow>().singleton()
    .each(detail::MainCameraSizeController);


  

} //end of Graphics::Graphics()

} //namespace engine
