
add_library(engine
  src/engine.cpp
  src/debug.cpp
  src/log.cpp
  src/graphics.cpp

  include/engine/world/world-object.hpp
  include/engine/world/transform.hpp
  include/engine/world/graphics.hpp
  include/engine/world/spatial.hpp
  src/world/world.cpp
  src/modules.hpp
  src/world/components.cpp
  include/engine/reflection.hpp
  src/reflection.cpp
  include/engine/lib/assert.hpp
  include/engine/world/world.hpp
  src/world/systems.cpp
  src/world/observers.cpp
  include/engine/lib/entry_consts.hpp
  include/engine/lib/mat3_decompose.hpp
  include/engine/command.hpp src/command.cpp
)

add_library(engine::engine ALIAS engine)

target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(engine PUBLIC
  flecs::flecs_static
  spdlog::spdlog
  glm_libs
  )

target_link_libraries(engine PRIVATE
  engine::sokol
  )

if (BUILD_TESTING)
  add_subdirectory(tests)
endif()


