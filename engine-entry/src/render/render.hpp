#pragma once
#include <flecs.h>
#include <engine/world/graphics.hpp>

namespace engine::render_backend {

namespace consts {

constexpr world::Color buffer_clear_color = {0.2, 0.2, 0.2};

} //end of namespace consts;

struct PhaseRenderBeginPre {};
struct PhaseRenderBegin {};

struct PhaseRenderOrderedPre {};
struct PhaseRenderOrdered {};

struct PhaseCommitPre {};
struct PhaseCommit {};


} //end of namespace engine::render_backend

namespace engine {

struct RenderBackend {
  RenderBackend(flecs::world&);
};

} //end of namespace engine;