#include <spdlog/spdlog.h>
#include <glm/gtx/matrix_transform_2d.hpp>
#include "graphics-backend-sfml.hpp"
#include "window.hpp"
#include "geometry.hpp"
#include "graphics.hpp"
#include "window-backend-sfml.hpp"
#include "transform.hpp"

namespace engine::graphics_backend_sfml::detail {

void AddRenderTarget(flecs::entity e) {
  const window_backend_sfml::MainWindowSFML* sfml_window = e.world().get<window_backend_sfml::MainWindowSFML>();
  e.set<RenderTarget>({.target = sfml_window->window});
}

void UpdateSquare(flecs::iter it,
                  Square* sfml_square,
                  const geometry::Square* geometry_square,
                  const graphics::Color* color,
                  const graphics::Transparency* transparency)
{
  if (!it.changed()) {
    it.skip();
    return;
  }
  for (auto i : it) {
    sfml_square[i].rect.setSize(sf::Vector2f(geometry_square[i].size, geometry_square[i].size));
    sfml_square[i].rect.setPosition(sf::Vector2f(-geometry_square[i].size / 2.0f, -geometry_square[i].size / 2.0f));
  }
  if (color && transparency) {
    for (auto i : it) {
      sfml_square[i].rect.setFillColor(sf::Color(color[i].r, color[i].g, color[i].b, transparency[i].a));
    }
  } else if (color && !transparency) {
    for (auto i : it) {
      sfml_square[i].rect.setFillColor(sf::Color(color[i].r, color[i].g, color[i].b, 255));
    }
  } else if (!color && transparency) {
    for (auto i : it) {
      sfml_square[i].rect.setFillColor(sf::Color(255,255,255, transparency[i].a));
    }
  } else {
    for (auto i : it) {
      sfml_square[i].rect.setFillColor(sf::Color::White);
    }
  }
}

static inline sf::Transform mat3_to_sf_transform(const glm::mat3& mat) {
  return sf::Transform(mat[0][0], mat[1][0], mat[2][0],
                       mat[0][1], mat[1][1], mat[2][1],
                       mat[0][2], mat[1][2], mat[2][2]);
}

void RenderSystem(flecs::iter it,
                  const geometry::Rectangle* camera_rect,
                  const RenderTarget* camera_rtarget,
                  const transform::Transform2* camera_transform,
                  const transform::Transform2* self_tranform,
                  const Square* self_square)
{
  for (auto i : it) {
    glm::vec2 cell_size;
    {
      sf::Vector2u rtarget_size = camera_rtarget[i].target->getSize();
      cell_size.x = static_cast<float>(rtarget_size.x) / camera_rect[i].width;
      cell_size.y = static_cast<float>(rtarget_size.y) / camera_rect[i].height;
    }
    glm::mat3 mat_screen_space = glm::mat3(1.0f);
    mat_screen_space = glm::scale(mat_screen_space, {cell_size.x, -cell_size.y});
    mat_screen_space = glm::translate(mat_screen_space, {0.0f, -camera_rect[i].height});
    //перемещение точки x:0,y:0 в центр экрана
    mat_screen_space = glm::translate(mat_screen_space, {camera_rect[i].width / 2.0f, camera_rect[i].height / 2.0f});
    
    glm::mat3 mat_camera_space = glm::inverse(camera_transform[i].value) * self_tranform[i].value;

    sf::RenderStates states;
    states.transform = mat3_to_sf_transform(mat_screen_space * mat_camera_space);

    camera_rtarget[i].target->draw(self_square[i].rect, states);
  }
}

} //engine::graphics_backend_sfml::detail

namespace engine {
using namespace graphics_backend_sfml;

GraphicsBackendSFML::GraphicsBackendSFML(flecs::world& world) {
  world.import<Window>();
  world.import<Geometry>();
  world.import<Graphics>();
  world.import<Transform>();
  world.import<WindowBackendSfml>();

  world.module<GraphicsBackendSFML>("graphics_backend_sfml");

  //components
  world.component<RenderTarget>();

  //systems 
  world.system("system::AddRenderTarget")
    .with<window_backend_sfml::MainWindowSFML>().singleton()
    .with<graphics::MainWindowCamera>()
    .without<RenderTarget>()
    .each(detail::AddRenderTarget);

  world.system<Square, const geometry::Square, const graphics::Color, const graphics::Transparency>("system::UpdateSquare")
    .kind(flecs::PreStore)
    .arg(3).optional()
    .arg(4).optional()
    .with<graphics::RenderedBy>().second(flecs::Wildcard)
    .iter(detail::UpdateSquare);

  world.system<const geometry::Rectangle,
               const RenderTarget,
               const transform::Transform2,
               const transform::Transform2,
               const Square>("system::RenderSystem")
    .kind(flecs::OnStore)
    .arg(1).up<graphics::RenderedBy>()
    .arg(2).up<graphics::RenderedBy>()
    .arg(3).up<graphics::RenderedBy>()
    .iter(detail::RenderSystem);
}

} //namespace engine