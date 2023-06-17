message("----- CONFIGURING SOKOL -----")

set(ENGINE_SOKOL_GFX_BACKEND "d3d11" CACHE STRING "sokol render backend")
set_property(CACHE ENGINE_SOKOL_GFX_BACKEND PROPERTY STRINGS
 "glcore3.3" "gles3" "d3d11" "metal" "wgpu" "dummy backend"
)

add_library(engine-sokol INTERFACE)
add_library(engine::sokol ALIAS engine-sokol)
target_include_directories(engine-sokol INTERFACE ${CMAKE_SOURCE_DIR}/dep/sokol)

if(ENGINE_SOKOL_GFX_BACKEND STREQUAL "glcore3.3")
  target_compile_definitions(engine-sokol INTERFACE SOKOL_GLCORE33)
elseif(ENGINE_SOKOL_GFX_BACKEND STREQUAL "gles3")
  target_compile_definitions(engine-sokol INTERFACE SOKOL_GLES3)
elseif(ENGINE_SOKOL_GFX_BACKEND STREQUAL "d3d11")
  target_compile_definitions(engine-sokol INTERFACE SOKOL_D3D11)
elseif(ENGINE_SOKOL_GFX_BACKEND STREQUAL "metal")
  target_compile_definitions(engine-sokol INTERFACE SOKOL_METAL)
elseif(ENGINE_SOKOL_GFX_BACKEND STREQUAL "wgpu")
  target_compile_definitions(engine-sokol INTERFACE SOKOL_WGPU)
elseif(ENGINE_SOKOL_GFX_BACKEND STREQUAL "dummy backend")
  target_compile_definitions(engine-sokol INTERFACE SOKOL_DUMMY_BACKEND)
else()
  message(FATAL_ERROR "'${ENGINE_SOKOL_GFX_BACKEND}' - is unknown sokol gfx backend")
endif()

if(UNIX)
  find_package(X11 REQUIRED)
  target_link_libraries(engine-sokol INTERFACE X11::X11 X11::Xcursor X11::Xi)

  find_package(OpenGL REQUIRED)
  target_link_libraries(engine-sokol INTERFACE OpenGL::GL)
endif()

message("-------------------------------------")
message(${CMAKE_BINARY_DIR})