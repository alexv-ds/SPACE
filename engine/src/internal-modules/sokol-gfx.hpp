#pragma once
#include <atomic>
#include <flecs.h>
#include <sokol_gfx.h>

namespace engine::internal {

  namespace module {
    struct SokolGfx {
      SokolGfx(flecs::world&);
    };
  } //namespace module

/**
 * @brief Синглтон копмонент. Его наличие говорит об инициализированном 
 * gfx контексте.
 */
class SokolGfxContext {
  //sg_pass_action main_window_action = {};
};

} //namespace engine::internal