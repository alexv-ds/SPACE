#pragma once

#include <spdlog/spdlog.h>

#define ENGINE_TRACE(...)  SPDLOG_TRACE(__VA_ARGS__)
#define ENGINE_DEBUG(...)  SPDLOG_DEBUG(__VA_ARGS__)
#define ENGINE_INFO(...)  SPDLOG_INFO(__VA_ARGS__)
#define ENGINE_WARN(...)  SPDLOG_WARN(__VA_ARGS__)
#define ENGINE_ERROR(...)  SPDLOG_ERROR(__VA_ARGS__)
#define ENGINE_CRITICAL(...)  SPDLOG_CRITICAL(__VA_ARGS__)
