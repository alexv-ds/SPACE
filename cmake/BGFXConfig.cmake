message("----- CONFIGURING BGFX -----")

set(BGFX_BUILD_TOOLS OFF CACHE BOOL "")
set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BGFX_INSTALL OFF CACHE BOOL "")
set(BGFX_CUSTOM_TARGETS OFF CACHE BOOL "")

set(BGFX_BUILD_TOOLS ON CACHE BOOL "" FORCE)
set(BGFX_BUILD_TOOLS_BIN2C OFF CACHE BOOL "")
set(BGFX_BUILD_TOOLS_GEOMETRY OFF CACHE BOOL "")
set(BGFX_BUILD_TOOLS_TEXTURE OFF CACHE BOOL "")


set(BGFX_DIR "${CMAKE_CURRENT_LIST_DIR}/../dep/bgfx-cmake/bgfx" CACHE PATH "" FORCE)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../dep/bgfx-cmake)