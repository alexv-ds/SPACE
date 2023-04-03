#pragma once
#include <string_view>

#define ENGINE_BGFX_DEFINE_CVARNAME(x) constexpr const char* const x = "::engine::bgfx::cvar::" #x

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

ENGINE_BGFX_DEFINE_CVARNAME(mainwindow_clear_depth); //1 or 0
ENGINE_BGFX_DEFINE_CVARNAME(mainwindow_clear_stencil); //1 or 0
ENGINE_BGFX_DEFINE_CVARNAME(mainwindow_clear_color_value); //hex string rgba example: "0xff0000ff"
ENGINE_BGFX_DEFINE_CVARNAME(mainwindow_clear_depth_value); //float value
ENGINE_BGFX_DEFINE_CVARNAME(mainwindow_clear_stencil_value); //from 0 to 255

} //namespace engine::bgfx::cvar


#undef ENGINE_BGFX_DEFINE_CVARNAME