#pragma once
#include <memory>
#include <flecs.h>
#include <bgfx/bgfx.h>
#include "graphics-backend-bgfx/BgfxLock.hpp"

namespace engine {

struct GraphicsBackendBGFX {
  GraphicsBackendBGFX(flecs::world&);
};

} //namespace engine


namespace engine::graphics_backend_bgfx {

struct Bgfx {
  std::shared_ptr<BgfxLock> lock;
};




} //namespace engine::graphics_backend_bgfx