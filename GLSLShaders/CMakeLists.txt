set(glslshaders_files
  DefaultPS.glsl
  DefaultVS.glsl
  )
add_custom_target(GLSLShaders SOURCES ${glslshaders_files})
foreach(var IN LISTS glslshaders_files)
        add_custom_command(TARGET GLSLShaders POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
                            ${CMAKE_CURRENT_SOURCE_DIR}/${var} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach(var)
