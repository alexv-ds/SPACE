message("----- CONFIGURING SPDLOG -----")
set(SPDLOG_USE_STD_FORMAT ON CACHE BOOL "")
set(SPDLOG_ENABLE_PCH ON CACHE BOOL "")
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../dep/spdlog)


