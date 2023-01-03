message("----- CONFIGURING FLECS -----")
option(FLECS_SHARED_LIBS OFF)
option(FLECS_SHARED OFF)
option(FLECS_PIC OFF)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../dep/flecs)


