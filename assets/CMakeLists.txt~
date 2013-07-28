set(asset_files
	TestObj.obj
	)
add_custom_target(assets SOURCES ${asset_files})
add_custom_command(TARGET assets PRE_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:SimpleEditor>)