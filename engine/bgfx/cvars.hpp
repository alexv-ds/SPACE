#pragma once
#include <string_view>

#define ENGINE_BGFX_DEFINE_CVARNAME(x) constexpr std::string_view x = "::engine::bgfx::cvar::" #x

namespace engine::bgfx::cvar {

using namespace std::string_view_literals;

ENGINE_BGFX_DEFINE_CVARNAME(vsync);
ENGINE_BGFX_DEFINE_CVARNAME(maxanisotropy);
ENGINE_BGFX_DEFINE_CVARNAME(capture);
ENGINE_BGFX_DEFINE_CVARNAME(flush_after_render);

ENGINE_BGFX_DEFINE_CVARNAME(debug_wireframe);
ENGINE_BGFX_DEFINE_CVARNAME(debug_ihf);
ENGINE_BGFX_DEFINE_CVARNAME(debug_stats);
ENGINE_BGFX_DEFINE_CVARNAME(debug_text);
ENGINE_BGFX_DEFINE_CVARNAME(debug_profiler);

} //namespace engine::bgfx::cvar


#undef ENGINE_BGFX_DEFINE_CVARNAME