cmake_minimum_required(VERSION 3.22.1)
project(SPACE VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  add_compile_options(/W3)
else()
  add_compile_options(-Wall)
endif()

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "")
endif()

add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)

find_package(SFML REQUIRED)
find_package(FLECS REQUIRED)
find_package(SPDLOG REQUIRED)
find_package(GLM REQUIRED)
find_package(BGFX REQUIRED)

add_executable(main
  engine/engine/main.cpp
  engine/engine/setup_spdlog.cpp
  engine/engine/flecs_helpers.cpp

  engine/filesystem-backend-stdlib.cpp
  engine/filesystem.cpp
  engine/geometry.cpp
  engine/glm-reflection.cpp
  #engine/modules/graphics-backend-sfml.cpp
  engine/graphics.cpp
  engine/transform.cpp
  engine/window-backend-sfml.cpp
  engine/window.cpp
  #engine/graphics-backend-bgfx.cpp
  engine/bgfx.cpp
  engine/bgfx/BgfxLock.cpp
  engine/bgfx/bgfx_cvars.cpp
  engine/bgfx/internal_components.cpp
  engine/cvar.cpp


  #"${CMAKE_SOURCE_DIR}/shaders/fs_test.sc"
)

target_link_libraries(main PRIVATE
  SFML::SFML
  flecs::flecs_static
  spdlog::spdlog
  glm_libs
  bgfx
  bx
)
add_dependencies(main shaderc)


add_executable(game
  game/main.cpp
  game/powernet.cpp
  engine/engine/setup_spdlog.cpp
  game/atmospherics.cpp
)
target_link_libraries(game PRIVATE flecs::flecs_static spdlog::spdlog)

#list (APPEND FOR_COMPILE_SHADERS
#  "${CMAKE_SOURCE_DIR}/shaders/fs_test.sc"
#)

function(compile_shader TARGET IN_FILE OUT_DIR DEF_FILE)
  string(REGEX MATCH "fs_.*\\.sc$" MATCH_RESULT ${IN_FILE})
  if(MATCH_RESULT)
    set(SHADER_TYPE "fragment")
  else()
    set(SHADER_TYPE "vertex")
  endif()

  get_filename_component(SHADER_FILENAME "${IN_FILE}" NAME_WLE)
  add_custom_command(
    OUTPUT "${OUT_DIR}/${SHADER_FILENAME}.spirv.bin"
    COMMAND shaderc -f "${IN_FILE}" -o "${OUT_DIR}/${SHADER_FILENAME}.spirv.bin" --profile spirv --varyingdef "${DEF_FILE}" --type "${SHADER_TYPE}"
    MAIN_DEPENDENCY "${IN_FILE}"
    DEPENDS shaderc
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  )

  target_sources(${TARGET} PRIVATE "${IN_FILE}")
endfunction()

compile_shader(
  main
  "${CMAKE_SOURCE_DIR}/shaders/fs_test.sc"
  "${CMAKE_SOURCE_DIR}/compiled_shaders"
  "${CMAKE_SOURCE_DIR}/shaders/varying.def.sc"
)

compile_shader(
  main
  "${CMAKE_SOURCE_DIR}/shaders/vs_test.sc"
  "${CMAKE_SOURCE_DIR}/compiled_shaders"
  "${CMAKE_SOURCE_DIR}/shaders/varying.def.sc"
)