cmake_minimum_required(VERSION 3.22.1)
project(SPACE VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(/W3)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "")
endif()

add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)

find_package(SFML REQUIRED)
find_package(FLECS REQUIRED)
find_package(SPDLOG REQUIRED)
find_package(GLM REQUIRED)

add_executable(main
  engine/main.cpp
  engine/setup_spdlog.cpp

  engine/modules/window.cpp
  engine/modules/window-backend-sfml.cpp
  engine/modules/filesystem.cpp
  engine/modules/filesystem-backend-stdlib.cpp
  engine/modules/transform.cpp
  engine/modules/graphics.cpp
  engine/modules/geometry.cpp
  engine/modules/glm-reflection.cpp
  engine/modules/graphics-backend-sfml.cpp
)

target_link_libraries(main PRIVATE
  SFML::SFML
  flecs::flecs_static
  spdlog::spdlog
  glm_libs
)

add_executable(game
  game/main.cpp
  game/powernet.cpp
  engine/setup_spdlog.cpp
)
target_link_libraries(game PRIVATE flecs::flecs_static spdlog::spdlog)