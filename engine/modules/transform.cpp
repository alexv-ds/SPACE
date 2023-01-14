#include <spdlog/spdlog.h>
#include <glm/gtx/matrix_transform_2d.hpp>
#include "transform.hpp"

namespace engine::transform::detail {

void AddTransform(flecs::entity e) {
  e.set<Transform2>({
    .value = glm::mat3(1.0f)
  });
}

void RemoveTransform(flecs::entity e) {
  e.remove<Transform2>();
}

void ApplyTransform(flecs::iter       it,
                    Transform2*       transform_out,
                    const Position2*  position, 
                    const Rotation2*  rotation, 
                    const Scale2*     scale)
{
  
  if (!it.changed()) {
    it.skip();
    return;
  }
  for (auto i : it) {
    transform_out[i].value = glm::mat3(1.0f);
  }
  if (position) {
    for (auto i : it) {
      transform_out[i].value = glm::translate(transform_out[i].value, glm::vec2(position[i].x, position[i].y));
    }
  }
  if (rotation) {
    for (auto i : it) {
      transform_out[i].value = glm::rotate(transform_out[i].value, rotation[i].angle);
    }
  }
  if (scale) {
    for (auto i : it) {
      transform_out[i].value = glm::scale(transform_out[i].value, glm::vec2(scale[i].x, scale[i].y));
    }
  }
} //function end





} //namespace engine::transform::detail

namespace engine {
using namespace transform;

Transform::Transform(flecs::world& world) {
  world.module<Transform>("transform");
  
  world.component<Position2>()
    .member<decltype(Position2::x)>("x")
    .member<decltype(Position2::y)>("y");

  world.component<Scale2>()
    .member<decltype(Scale2::x)>("x")
    .member<decltype(Scale2::y)>("y");

  world.component<Rotation2>()
    .member<decltype(Rotation2::angle), flecs::units::angle::Radians>("angle");

  world.component<Transform2>();

  //systems
  world.system("system::AddTransform")
    .multi_threaded()
    .kind(flecs::OnValidate)
    .without<Transform2>().out()
    .with<Position2>().or_()
    .with<Rotation2>().or_()
    .with<Scale2>().or_()
    .each(detail::AddTransform);
  
  world.system("system::RemoveTransform")
    .multi_threaded()
    .with<Transform2>().out()
    .without<Position2>()
    .without<Rotation2>()
    .without<Scale2>()
    .each(detail::RemoveTransform);
  
  world.system<Transform2, const Position2, const Rotation2, const Scale2>("system::ApplyTransform")
    //.multi_threaded() //не работает совместно с отслеживанием изменений таблицы
    .instanced()
    .term_at(2).or_()
    .term_at(3).or_()
    .term_at(4).or_()
    .iter(detail::ApplyTransform);

}

} //namespace engine