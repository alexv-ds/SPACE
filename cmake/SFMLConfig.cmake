message("----- CONFIGURING SFML -----")
option(SFML_BUILD_AUDIO off)
option(SFML_BUILD_NETWORK off)
option(SFML_BUILD_GRAPHICS on)
option(WARNINGS_AS_ERRORS off)
option(BUILD_SHARED_LIBS off)

add_subdirectory(dep/SFML)
add_library(sfml-libs INTERFACE)
add_library(SFML::SFML ALIAS sfml-libs)
target_link_libraries(sfml-libs INTERFACE sfml-system sfml-window sfml-graphics)

if(WIN32)
  target_link_libraries(sfml-main)    
endif()



