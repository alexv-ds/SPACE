#include "engine/lib/log.hpp"

namespace engine {

void sokol_logfunc(
  const char* /*tag*/, // always "sapp"
  std::uint32_t log_level, // 0=panic, 1=error, 2=warning, 3=info
  std::uint32_t log_item_id, // SAPP_LOGITEM_*
  const char* message_or_null, // alpha message string, may be nullptr in release mode
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

} //namespace engine;