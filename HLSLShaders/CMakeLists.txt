set(hlsl_h
	LightStructs.hlsl
	ForwardLighting.hlsl
	)
set(hlsl_ps
	DefaultPS.hlsl
	DebugPS.hlsl
	BillboardPS.hlsl
	)
set(hlsl_vs
	DefaultVS.hlsl
	DebugVS.hlsl
	BillboardVS.hlsl
	)
find_program(FXC fxc DOC "fx compiler")

add_custom_target(HLSLShaders SOURCES ${hlsl_vs} ${hlsl_ps} ${hlsl_h})
foreach(var ${hlsl_vs})
	get_filename_component(file_we ${var} NAME_WE)
	add_custom_command(TARGET HLSLShaders
					   POST_BUILD
					   COMMAND ${FXC} /T "vs_5_0" /Od /Zi /Fo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${file_we}.cso ${CMAKE_CURRENT_SOURCE_DIR}/${var}
					   COMMENT "Effect-compile ${var}"
					   )
endforeach(var)
foreach(var ${hlsl_ps})
	get_filename_component(file_we ${var} NAME_WE)
	add_custom_command(TARGET HLSLShaders
					   POST_BUILD
					   COMMAND ${FXC} /T "ps_5_0" /Od /Zi /Fo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${file_we}.cso ${CMAKE_CURRENT_SOURCE_DIR}/${var}
					   COMMENT "Effect-compile ${var}"
					   )
endforeach(var)
