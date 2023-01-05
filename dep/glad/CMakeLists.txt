add_library(glad STATIC src/gl.c)
add_library(glad::glad ALIAS glad)
target_include_directories(glad PUBLIC include)