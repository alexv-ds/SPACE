#pragma once
#include <string>
#include <cstdint>
#include "../cvar/define_helper.hpp"

#define ENGINE_BGFX_DEFINE_CVARNAME(Type, Symbol) ENGINE_CVAR_DEFINE(Type, Symbol, "::engine::bgfx::cvar::" #Symbol)


namespace engine::bgfx::cvar {

using namespace std::string_view_literals;

ENGINE_BGFX_DEFINE_CVARNAME(bool, vsync);
ENGINE_BGFX_DEFINE_CVARNAME(bool, maxanisotropy);
ENGINE_BGFX_DEFINE_CVARNAME(bool, capture);
ENGINE_BGFX_DEFINE_CVARNAME(bool, flush_after_render);

ENGINE_BGFX_DEFINE_CVARNAME(bool, debug_wireframe);
ENGINE_BGFX_DEFINE_CVARNAME(bool, debug_ihf);
ENGINE_BGFX_DEFINE_CVARNAME(bool, debug_stats);
ENGINE_BGFX_DEFINE_CVARNAME(bool, debug_text);
ENGINE_BGFX_DEFINE_CVARNAME(bool, debug_profiler);

ENGINE_BGFX_DEFINE_CVARNAME(bool, mainwindow_clear_depth);
ENGINE_BGFX_DEFINE_CVARNAME(bool, mainwindow_clear_stencil);
ENGINE_BGFX_DEFINE_CVARNAME(std::uint32_t, mainwindow_clear_color_value);
ENGINE_BGFX_DEFINE_CVARNAME(float, mainwindow_clear_depth_value);
ENGINE_BGFX_DEFINE_CVARNAME(std::uint8_t, mainwindow_clear_stencil_value);

ENGINE_BGFX_DEFINE_CVARNAME(std::string, render_backend);


} //namespace engine::bgfx::cvar


#undef ENGINE_BGFX_DEFINE_CVARNAME