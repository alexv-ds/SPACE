#include <sokol_app.h>
#include <sokol_gfx.h>
#include "../sokol_gp.h"

#include <engine/lib/log.hpp>
#include <engine/lib/entry_consts.hpp>
#include <engine/lib/mat3_decompose.hpp>
#include <engine/world/world.hpp>
#include "render.hpp"
#include <util/sokol_imgui.h>
#include <glm/gtx/matrix_transform_2d.hpp>

namespace engine::render_backend {

static int layer_comparator(const flecs::entity_t,
                            const world::Layer* const l1,
                            const flecs::entity_t,
                            const world::Layer* const l2) {
  const float layer1 = l1 ? l1->layer : 0.0f;
  const float layer2 = l2 ? l2->layer : 0.0f;
  return (layer1 > layer2) - (layer1 < layer2);
}

static void RenderBegin(flecs::iter it) {
  const flecs::world world = it.world();
  // Get current window size.
  const int width = sapp_width();
  const int height = sapp_height();

  sgp_begin(width, height);
  sgp_viewport(0, 0, width, height);

  //set project
  sgp_project(-0.5f, 0.5f, 0.5f, -0.5f);
  {
    flecs::entity main_camera = world.entity(entry_consts::main_camera_name);
    const auto* const p_position = main_camera.get<world::Position>();
    const auto* const p_rotation = main_camera.get<world::Rotation>();
    const auto* const p_scale = main_camera.get<world::Scale>();

    const world::Position
      position = p_position ? *p_position : world::Position{.x = 0.0f, .y = 0.0f};
    const world::Rotation rotation = p_rotation ? *p_rotation : world::Rotation{.angle = 0.0f};
    const world::Scale scale = p_scale ? *p_scale : world::Scale{.x = 1.0f, .y = 1.0f};

    sgp_translate(-position.x, -position.y);
    sgp_rotate(rotation.angle);
    sgp_scale(1.0f / scale.x, 1.0f / scale.y);
  }

  sgp_set_color(consts::buffer_clear_color.r,
                consts::buffer_clear_color.g,
                consts::buffer_clear_color.b,
                1.0f);
  sgp_clear();

  sg_pass_action pass_action = {};
  sg_begin_default_pass(pass_action, width, height);
}

static void StoreOrdered(flecs::iter it,
                         const world::WorldObject* world_object,
                         const world::Position* position,
                         const world::Rotation* rotation, //optional
                         const world::Scale* scale, //optional
                         const world::Transparency* transparency, //optional
                         const world::Color* color, //optional
                         const world::Layer*) //optional
{
  for (auto i : it) {
    sgp_push_transform();
    sgp_translate(position->x, position->y);

    if (rotation) {
      sgp_rotate(-rotation->angle);
    }

    if (scale) {
      sgp_scale(scale->x, scale->y);
    }

    const world::Color draw_color = color ? color[i] : world::color::white;
    const float alpha = transparency ? transparency[i].alpha : 1.0f;
    sgp_set_color(draw_color.r, draw_color.g, draw_color.b, alpha);
    sgp_draw_filled_rect(-world_object->size_x / 2.0f,
                         -world_object->size_y / 2.0f,
                         world_object->size_x,
                         world_object->size_y);
    sgp_pop_transform();
  }
}

static void Commit(flecs::iter it) {
  sgp_flush();
  sgp_end();
  simgui_render();
  sg_end_pass();
  sg_commit();
}

static void ImguiNewFrame(flecs::iter it) {
  const int width = sapp_width();
  const int height = sapp_height();
  simgui_new_frame({width, height, sapp_frame_duration(), sapp_dpi_scale()});
}

void init_systems(flecs::world & world) {
  [[maybe_unused]] auto scope = world.scope(world.entity("system"));

  world.system("RenderBegin")
    .kind<PhaseBegin>()
    .iter(RenderBegin);

  world.system<const world::WorldObject,
               const world::Position,
               const world::Rotation,
               const world::Scale,
               const world::Transparency,
               const world::Color,
               const world::Layer>("StoreOrdered")
    .kind<PhaseStoreOrdered>()
    .arg(3).optional()
    .arg(4).optional()
    .arg(5).optional()
    .arg(6).optional()
    .arg(7).optional()
    .with<world::Renderable>()
      //.order_by(layer_comparator)
    .iter(StoreOrdered);

  world.system("Commit")
    .kind<PhaseCommit>()
    .iter(Commit);

  world.system("ImGuiNewFrame")
    .kind(flecs::PreStore)
    .iter(ImguiNewFrame);
}

} //end of namespace engine::render_backend