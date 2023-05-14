#include <string>
#include <cstdint>
#include <cstdlib>
#include <engine/engine.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>

#ifdef _WIN32
  #include <windows.h>
#endif

#define SOKOL_GFX_IMPL
#include <sokol_gfx.h>

#define SOKOL_APP_IMPL 
#define SOKOL_WIN32_FORCE_MAIN
#include <sokol_app.h>

#include <imgui.h>
#define SOKOL_IMGUI_IMPL
#include <util/sokol_imgui.h>

#define SOKOL_GLUE_IMPL
#include <sokol_glue.h>

#include <engine/debug/imgui.hpp>




///@brief https://github.com/gabime/spdlog/blob/57a9fd0841f00e92b478a07fef62636d7be612a8/include/spdlog/details/os-inl.h#L600
std::string getenv_safe(const char *field) {
#if defined(_MSC_VER)
#    if defined(__cplusplus_winrt)
    return std::string{}; // not supported under uwp
#    else
    size_t len = 0;
    char buf[128];
    bool ok = ::getenv_s(&len, buf, sizeof(buf), field) == 0;
    return ok ? buf : std::string{};
#    endif
#else // revert to getenv
    char *buf = ::getenv(field);
    return buf ? buf : std::string{};
#endif
}

static void sokol_logfunc(
  const char* /*tag*/, // always "sapp"
  std::uint32_t log_level, // 0=panic, 1=error, 2=warning, 3=info
  std::uint32_t log_item_id, // SAPP_LOGITEM_*
  const char* message_or_null, // a message string, may be nullptr in release mode
  std::uint32_t line_nr, // line number in sokol_app.h
  const char* filename_or_null, // source filename, may be nullptr in release mode
  void* /*user_data*/
)
{
  const char* const message = message_or_null == nullptr ? "MSG UNAVALIABLE. COMPILE WITH DEBUG" : message_or_null;
  spdlog::level::level_enum spdlog_level;
  switch (log_level) {
    case 0: {
      spdlog_level = spdlog::level::critical;
      break;
    }
    case 1: {
      spdlog_level = spdlog::level::err;
      break;
    }
    case 2: {
      spdlog_level = spdlog::level::warn;
      break;
    }
    default: {
      spdlog_level = spdlog::level::trace;
    }
  }

  spdlog::logger* const logger = spdlog::default_logger_raw();
  logger->log(
    spdlog::source_loc{filename_or_null, static_cast<int>(line_nr), nullptr},
    spdlog_level,

    "log item id: {}, msg: {}", log_item_id, message
  );
}

static std::shared_ptr<flecs::world> g_world = nullptr;
static int g_argc = 0;
static char** g_argv = nullptr;
static sg_pass_action g_pass_action = {};

/// @brief точка входа приложения
void engine_main(flecs::world&);

static void init_cb() {
  g_world = engine::create_world(g_argc, g_argv);
  engine_main(*g_world);

  sg_setup({
    .logger = {
      .func = sokol_logfunc
    },
    .context = sapp_sgcontext()
  });

  simgui_setup({
    .ini_filename = "imgui.ini"
  });

  g_world->add<engine::debug::ImGuiContext>();

  g_pass_action.colors[0].action = SG_ACTION_CLEAR;
  g_pass_action.colors[0].value = {0.1f, 0.1f, 0.1f, 1.0f};
};

static void cleanup_cb() {
  g_world->quit();
  g_world = nullptr;

  simgui_shutdown();
  sg_shutdown();
};

static void frame_cb() {
  const float delta_time = sapp_frame_duration();

  //imgui prepare
  const int width = sapp_width();
  const int height = sapp_height();
  simgui_new_frame({width, height, delta_time, sapp_dpi_scale()});

  //update world
  bool is_countinue = engine::update_world(g_world, delta_time);
  if (!is_countinue) {
    sapp_request_quit();
  }

  //render
  sg_begin_default_pass(&g_pass_action, width, height);
  simgui_render();
  sg_end_pass();
  sg_commit();
};

void event_cb(const sapp_event* event) {
  simgui_handle_event(event);
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
  if (getenv_safe("SPDLOG_LEVEL").size() > 0) {
    spdlog::cfg::load_env_levels();
  }  

  return {
    .init_cb = init_cb,
    .frame_cb = frame_cb,
    .cleanup_cb = cleanup_cb,
    .event_cb = event_cb,
    .width = 1400,
    .height = 800,
    .sample_count = 8,
    .swap_interval = 1,
    //.high_dpi = false
    .window_title = "engine",
    .logger = {
      .func = sokol_logfunc
    },

    .win32_console_utf8 = true
  };
}