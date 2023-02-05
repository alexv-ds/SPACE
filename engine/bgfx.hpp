#pragma once
#include <memory>
#include <cstdint>
#include <flecs.h>
#include "bgfx/BgfxLock.hpp"
#include "bgfx/cvars.hpp"

namespace engine {

struct Bgfx {
  Bgfx(flecs::world&);

  //internal
  std::uint32_t reset_flags;
};

} //namespace engine


namespace engine::bgfx {

  struct BgfxContext {
    std::shared_ptr<BgfxLock> lock;
  };

  struct DebugStats {};
} // namespace engine::bgfx
