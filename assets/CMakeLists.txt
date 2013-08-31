set(asset_files
	TestObj.obj
	Cone.obj
	Helix.obj
	)
add_custom_target(assets SOURCES ${asset_files})
add_custom_command(TARGET assets PRE_LINK 
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})