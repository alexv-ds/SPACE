set(EMSH_GENERATED_INCLUDE_DIR "${CMAKE_BINARY_DIR}/embeded_shaders_include/embeded_shaders")

add_library(embeded_shaders INTERFACE)
add_dependencies(embeded_shaders shaderc)
target_include_directories(embeded_shaders INTERFACE "${CMAKE_BINARY_DIR}/embeded_shaders_include") 

function (emsh_compile_to_header IN_FILE DEF_FILE)
  string(REGEX MATCH "fs_.*\\.sc$" MATCH_RESULT ${IN_FILE})
  if(MATCH_RESULT)
    set(SHADER_TYPE "fragment")
  else()
    set(SHADER_TYPE "vertex")
  endif()

  get_filename_component(SHADER_FILENAME "${IN_FILE}" NAME_WLE)
  set(OUT_DIR "${EMSH_GENERATED_INCLUDE_DIR}")

  list(APPEND USED_PROFILES
    #opengles
    #100_es 300_es 310_es 320_es 

    #apple
    #metal

    #playstation
    #pssl 

    #vulkan
    spirv #spirv10-10 spirv13-11 spirv14-11 spirv15-12 spirv16-13

    #opengl
    #120 130 140 150 330 400 410 420 430 440 
  )

  if (WIN32)
    #list(APPEND USED_PROFILES s_3_0 s_4_0 s_5_0) #directx
  endif()

  foreach(PROFILE IN LISTS USED_PROFILES)
    string(MAKE_C_IDENTIFIER "${SHADER_FILENAME}.${PROFILE}" ARRAY_NAME)
    #add_custom_command(
    #  OUTPUT "${OUT_DIR}/${SHADER_FILENAME}.${PROFILE}.h"
    #  COMMAND shaderc -f "${IN_FILE}" -o "${OUT_DIR}/${SHADER_FILENAME}.${PROFILE}.h" --profile "${PROFILE}" --varyingdef "${DEF_FILE}" --type "${SHADER_TYPE}" --bin2c "${ARRAY_NAME}"
    #  MAIN_DEPENDENCY "${IN_FILE}"
    #  DEPENDS shaderc
    #  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    #)
    add_custom_command(
      OUTPUT "${OUT_DIR}/${SHADER_FILENAME}.${PROFILE}.h"
      COMMAND shaderc -f "${IN_FILE}" -o "${OUT_DIR}/${SHADER_FILENAME}.${PROFILE}.h" --profile "${PROFILE}" --varyingdef "${DEF_FILE}" --type "${SHADER_TYPE}" --bin2c "${ARRAY_NAME}"
      DEPENDS "${IN_FILE}"
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
    target_sources(embeded_shaders PUBLIC "${OUT_DIR}/${SHADER_FILENAME}.${PROFILE}.h")
  endforeach()
endfunction()
