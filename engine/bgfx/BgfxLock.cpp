#include <bgfx/bgfx.h>
#include <spdlog/spdlog.h>
#include "BgfxLock.hpp"

namespace engine::bgfx {

BgfxLock::~BgfxLock() {
  SPDLOG_TRACE("BGFX SHUTDOWN");
  ::bgfx::shutdown();
}

} //namespace engine::bgfx 