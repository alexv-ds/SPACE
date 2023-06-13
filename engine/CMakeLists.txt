
add_library(engine
  src/engine.cpp
  src/debug.cpp
  src/log.cpp
  src/graphics.cpp

  src/internal-modules/sokol-gfx.cpp include/engine/graphics/drawable.hpp include/engine/graphics/graphics.hpp include/engine/world.hpp)
add_library(engine::engine ALIAS engine)

target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(engine PUBLIC
  flecs::flecs_static
  spdlog::spdlog
)

target_link_libraries(engine PRIVATE engine::sokol)
