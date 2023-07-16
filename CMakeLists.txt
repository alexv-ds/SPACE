cmake_minimum_required(VERSION 3.22.1)
project(SPACE VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

if(MSVC)
  add_compile_options(/W3)
else()
  add_compile_options(-Wall)
endif()

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "")
endif()

add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)

find_package(FLECS REQUIRED)
find_package(SPDLOG REQUIRED)
find_package(SOKOL REQUIRED)
find_package(IMGUI REQUIRED)
find_package(GLM REQUIRED)



add_subdirectory(engine)
add_subdirectory(engine-entry)

#public libs





#add_executable(main
#  engine/engine/main.cpp
#  engine/engine/setup_spdlog.cpp
#  engine/engine/flecs_helpers.cpp
#
#  engine/filesystem-backend-stdlib.cpp
#  engine/filesystem.cpp
#  engine/geometry.cpp
#  engine/glm-reflection.cpp
#  engine/graphics.cpp
#  engine/transform.cpp
#  engine/window-backend-sfml.cpp
#  engine/window.cpp
#  engine/cvar.cpp
#
#  engine/graphics-backend-sfml.cpp
#  engine/imgui.cpp
#  engine/imgui-backend-sfml.cpp
#)

#target_link_libraries(main PRIVATE
#  SFML::SFML
#  flecs::flecs_static
#  spdlog::spdlog
#  glm_libs
#  ImGui-SFML
#)

add_executable(game
  game/main.cpp
  game/powernet.cpp
#  engine/engine/setup_spdlog.cpp
#  game/atmospherics.cpp
  game/imgui-tools.hpp)
#target_link_libraries(game PRIVATE flecs::flecs_static spdlog::spdlog)
target_link_libraries(game PRIVATE engine::engine engine::entry engine::imgui)