set(hlsl_src
	defaultPS.hlsl
	defaultVS.hlsl
	)


add_custom_target(HLSLShaders SOURCES ${hlsl_src})
add_custom_command(TARGET assets POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_files *.cso $<TARGET_FILE_DIR:SimpleEditor>)