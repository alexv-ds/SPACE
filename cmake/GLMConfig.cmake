message("----- CONFIGURING GLM -----")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(BUILD_STATIC_LIBS ON CACHE BOOL "")
add_subdirectory(dep/glm)

add_library(glm_libs INTERFACE)

if(${BUILD_STATIC_LIBS})
  target_link_libraries(glm_libs INTERFACE glm::glm_static)
else()
target_link_libraries(glm_libs INTERFACE glm::glm)
endif()



