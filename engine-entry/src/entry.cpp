#include <string>
#include <cstdint>
#include <cstdlib>
#include "engine/lib/log.hpp"
#include <engine/engine.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>
#include <cmath>

#ifdef _WIN32

  #include <windows.h>

#endif

#define SOKOL_IMPL

#include <sokol_gfx.h>
#include "sokol_gp.h"

#define SOKOL_WIN32_FORCE_MAIN

#include <sokol_app.h>
#include <sokol_glue.h>

#include "render/render.hpp"

///@brief https://github.com/gabime/spdlog/blob/57a9fd0841f00e92b478a07fef62636d7be612a8/include/spdlog/details/os-inl.h#L600
std::string getenv_safe(const char* field) {
#if defined(_MSC_VER)
  #if defined(__cplusplus_winrt)
    return std::string{}; // not supported under uwp
  #else
    size_t len = 0;
    char buf[128];
    bool ok = ::getenv_s(&len, buf, sizeof(buf), field) == 0;
    return ok ? buf : std::string{};
  #endif
#else // revert to getenv
  char *buf = ::getenv(field);
  return buf ? buf : std::string{};
#endif
}

static std::shared_ptr<flecs::world> g_world = nullptr;
static int g_argc = 0;
static char** g_argv = nullptr;

/// @brief точка входа приложения
void engine_main(flecs::world & );

static void init2() {
  {
    g_world = engine::create_world(g_argc, g_argv);
    g_world->import<engine::RenderBackend>();
    engine_main(*g_world);

    sg_desc desc = {.logger = {.func = engine::sokol_logfunc}, .context = sapp_sgcontext()};
    sg_setup(desc);
    if (!sg_isvalid()) {
      ENGINE_CRITICAL("Failed to create Sokol GFX context!");
      std::exit(EXIT_FAILURE);
    }
  }

  {
    sgp_desc desc = {};
    sgp_setup(&desc);
    if (!sgp_is_valid()) {
      ENGINE_CRITICAL("Failed to create Sokol GP context: {}", sgp_get_error_message(sgp_get_last_error()));
      std::exit(EXIT_FAILURE);
    }
  }
}

static void frame2() {
  // Get current window size.
  const int width = sapp_width();
  const int height = sapp_height();

  //update world
  bool is_countinue = engine::update_world(g_world, static_cast<float>(sapp_frame_duration()));
  if (!is_countinue) {
    sapp_request_quit();
  }

  // Draw an animated rectangle that rotates and changes its colors.
  const float time = static_cast<float>(sapp_frame_count()) * static_cast<float>(sapp_frame_duration());
  const float r = std::sin(time) * 0.5f + 0.5f;
  const float g = std::cos(time) * 0.5f + 0.5f;
  sgp_set_color(r, g, 0.3f, 1.0f);
  //sgp_rotate_at(time*20.0f, 0.5f, 0.5f);
  //sgp_draw_filled_rect(-0.5f, -0.5f, 1.0f, 1.0f);

  sgp_draw_filled_rect(-0.5f, -0.5f, 1.0f, 1.0f);




  // Begin alpha render pass.
  sg_pass_action pass_action = {};
  sg_begin_default_pass(pass_action, width, height);
  // Dispatch all draw commands to Sokol GFX.
  sgp_flush();
  // Finish alpha draw command queue, clearing it.
  sgp_end();
  // End render pass.
  sg_end_pass();
  // Commit Sokol render.
  sg_commit();
}

static void cleanup2() {
  // Cleanup Sokol GP and Sokol GFX resources.
  sgp_shutdown();
  sg_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[]) {
  g_argc = argc;
  g_argv = argv;
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif
#ifndef NDEBUG
  spdlog::set_level(spdlog::level::trace);
#endif
  if (!getenv_safe("SPDLOG_LEVEL").empty()) {
    spdlog::cfg::load_env_levels();
  }
  return {.init_cb = init2, .frame_cb = frame2, .cleanup_cb = cleanup2, .sample_count = 4, .window_title = "Hi duddles"};
}