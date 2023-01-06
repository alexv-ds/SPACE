#include <glad/gl.h>
#include "opengl.hpp"
#include "window.hpp"

#include <spdlog/spdlog.h>

namespace engine::opengl {

void UpdateViewport(flecs::iter it, const window::MainWindow* window, const window::event::Resized*) {
  glViewport(0, 0, window->width, window->height);
}

void PreRenderClearWindow(flecs::iter it) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

}

namespace engine {
using namespace opengl;


Opengl::Opengl(flecs::world& world) {
  world.import<Window>();
  world.module<Opengl>("opengl");

  world.component<OpenglContext>();

  //systems
  world.system("system::PreRenderClearWindow")
    .term<OpenglContext>().singleton()
    .iter(PreRenderClearWindow);
  world.system<const window::MainWindow, const window::event::Resized>("system::UpdateViewport")
    .kind(flecs::PreStore)
    .term_at(1).parent()
    .iter(UpdateViewport);
}

} //namespace engine