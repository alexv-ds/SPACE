#include <cstdlib>
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>
#include "setup_spdlog.hpp"

#ifdef _WIN32
  #include <windows.h>
#endif

namespace engine {
  void setup_spdlog() {
  #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
  #endif
  #ifndef NDEBUG
    spdlog::set_level(spdlog::level::trace);  
  #endif
    if (std::getenv("SPDLOG_LEVEL")) {
      spdlog::cfg::load_env_levels();
    }    
  }
}
