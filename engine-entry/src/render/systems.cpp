#include <sokol_app.h>
#include <sokol_gfx.h>
#include "../sokol_gp.h"
#include "render.hpp"


namespace engine::render_backend {

void RenderBegin(flecs::iter it) {
  // Get current window size.
  const int width = sapp_width();
  const int height = sapp_height();
  const float ratio = static_cast<float>(width) / static_cast<float>(height);

  // Begin recording draw commands for alpha frame buffer of size (width, height).
  sgp_begin(width, height);
  // Set frame buffer drawing region to (0,0,width,height).
  sgp_viewport(0, 0, width, height);
  // Set drawing coordinate space to (left=-ratio, right=ratio, top=1, bottom=-1)
  sgp_project(-ratio*1, ratio*1, 1.0f, -1.0f); //TODO: ТУДУ БЛЯДЬ!!11

  // Clear the frame buffer.
  sgp_set_color(consts::buffer_clear_color.r, consts::buffer_clear_color.g, consts::buffer_clear_color.b, 1.0f);
  sgp_clear();




}

void init_systems(flecs::world& world) {
  [[maybe_unused]] auto scope = world.scope(world.entity("system"));

  world.system("RenderBegin")
    .kind<PhaseRenderBegin>()
    .iter(RenderBegin);


}

} //end of namespace engine::render_backend