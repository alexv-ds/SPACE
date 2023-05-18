
add_library(engine-entry
  src/entry.cpp
)
add_library(engine::entry ALIAS engine-entry)

#target_include_directories(engine-entry PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(engine-entry PUBLIC engine::engine)

target_link_libraries(engine-entry PRIVATE engine::sokol engine::imgui)