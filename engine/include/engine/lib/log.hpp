#pragma once

#include "spdlog/spdlog.h"

#define ENGINE_TRACE(...)  SPDLOG_TRACE(__VA_ARGS__)
#define ENGINE_DEBUG(...)  SPDLOG_DEBUG(__VA_ARGS__)
#define ENGINE_INFO(...)  SPDLOG_INFO(__VA_ARGS__)
#define ENGINE_WARN(...)  SPDLOG_WARN(__VA_ARGS__)
#define ENGINE_ERROR(...)  SPDLOG_ERROR(__VA_ARGS__)
#define ENGINE_CRITICAL(...)  SPDLOG_CRITICAL(__VA_ARGS__)

namespace engine {

void sokol_logfunc(
  const char* /*tag*/, // always "sapp"
  std::uint32_t log_level, // 0=panic, 1=error, 2=warning, 3=info
  std::uint32_t log_item_id, // SAPP_LOGITEM_*
  const char* message_or_null, // alpha message string, may be nullptr in release mode
  std::uint32_t line_nr, // line number in sokol_app.h
  const char* filename_or_null, // source filename, may be nullptr in release mode
  void* /*user_data*/
);

} //namespace engine