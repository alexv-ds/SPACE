add_library(glad STATIC src/glad.c)
add_library(glad::glad ALIAS glad)
target_include_directories(glad PUBLIC include)