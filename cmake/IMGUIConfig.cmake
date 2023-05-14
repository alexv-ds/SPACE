message("----- CONFIGURING IMGUI -----")

add_library(engine-imgui
  "${CMAKE_SOURCE_DIR}/dep/imgui/imgui_demo.cpp"
  "${CMAKE_SOURCE_DIR}/dep/imgui/imgui_draw.cpp"
  "${CMAKE_SOURCE_DIR}/dep/imgui/imgui_tables.cpp"
  "${CMAKE_SOURCE_DIR}/dep/imgui/imgui_widgets.cpp"
  "${CMAKE_SOURCE_DIR}/dep/imgui/imgui.cpp"
)
add_library(engine::imgui ALIAS engine-imgui)

target_include_directories(engine-imgui PUBLIC "${CMAKE_SOURCE_DIR}/dep/imgui")