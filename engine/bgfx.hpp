#pragma once
#include <memory>
#include <flecs.h>
#include "bgfx/BgfxLock.hpp"

namespace engine {

struct Bgfx {
  Bgfx(flecs::world&);
};

} //namespace engine


namespace engine::bgfx {

struct BgfxContext {
  std::shared_ptr<BgfxLock> lock;
};

} // namespace engine::bgfx
