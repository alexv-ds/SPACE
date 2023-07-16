#include <string>
#include <cstdint>
#include <cstdlib>
#include <engine/lib/log.hpp>
#include <engine/lib/entry_consts.hpp>
#include <engine/engine.hpp>
#include <engine/world/world.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>
#include <cmath>
#include <engine/debug/imgui.hpp>
#include <glm/vec2.hpp>

#ifdef _WIN32

  #include <windows.h>

#endif

#define SOKOL_IMPL

#include <sokol_gfx.h>
#include "sokol_gp.h"

#define SOKOL_WIN32_FORCE_MAIN

#include <sokol_app.h>
#include <sokol_glue.h>

#include <imgui.h>
#define SOKOL_IMGUI_IMPL
#include <util/sokol_imgui.h>

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

  //imgui
  {
    simgui_desc_t simgui_desc = {
      .ini_filename = "imgui.ini"
    };
    simgui_setup(&simgui_desc);
    g_world->add<engine::debug::ImGuiContext>();
  }

  //init camera
  g_world->entity(engine::entry_consts::main_camera_name)
    .add<engine::world::WorldObject>()
    .add<engine::world::HandleIntersections>();
}

static void frame2() {
/*  const float camera_base_x = 2;
  const float camera_base_y = 2;
  const float ratio = sapp_widthf() / sapp_heightf();
  auto* camera_scale = g_world->entity(engine::entry_consts::main_camera_name)
    .get_mut<engine::world::Scale>();
  camera_scale->x = camera_base_x * ratio;
  camera_scale->y = camera_base_y;*/

  glm::vec2 camera_base_size = glm::vec2(1.0f);
  flecs::entity main_camera = g_world->entity(engine::entry_consts::main_camera_name);
  {
    const auto* const camera_scale = main_camera.get<engine::world::Scale>();
    if (camera_scale) {
      camera_base_size.x = camera_scale->x;
      camera_base_size.y = camera_scale->y;
    }
  }
  const float ratio = sapp_widthf() / sapp_heightf();
  auto* camera_world_object = main_camera.get_mut<engine::world::WorldObject>();
  camera_world_object->size_y = 1.0f;
  camera_world_object->size_x = 1.0f * ratio;

  bool is_countinue = engine::update_world(g_world, static_cast<float>(sapp_frame_duration()));
  if (!is_countinue) {
    sapp_request_quit();
  }

}

static void cleanup2() {
  g_world = nullptr;
  // Cleanup Sokol GP and Sokol GFX resources.
  sgp_shutdown();
  simgui_shutdown();
  sg_shutdown();
}

static void input(const sapp_event* event) {
  if (!g_world) {
    return;
  }

  if (simgui_handle_event(event)) {
    return;
  }

  flecs::entity main_camera = g_world->entity(engine::entry_consts::main_camera_name);

  if (main_camera.has<engine::world::Position>()) {
    auto position = main_camera.get_mut<engine::world::Position>();
    const float move_speed = 0.1f;
    switch (event->key_code) {
      case SAPP_KEYCODE_W: {
        position->y += move_speed;
        break;
      }
      case SAPP_KEYCODE_S: {
        position->y -= move_speed;
        break;
      }
      case SAPP_KEYCODE_D: {
        position->x += move_speed;
        break;
      }
      case SAPP_KEYCODE_A: {
        position->x -= move_speed;
      }
    }
  }
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
  return {
    .init_cb = init2,
    .frame_cb = frame2,
    .cleanup_cb = cleanup2,
    .event_cb = input,
    .sample_count = 4,
    .window_title = "Hi duddles"
  };
}