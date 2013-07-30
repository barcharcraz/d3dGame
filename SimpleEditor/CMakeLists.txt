set(editor_src
	resource.h
	SimpleEditor.h
	SimpleEditor.cpp
	stdafx.h
	stdafx.cpp
	targetver.h
	)

add_executable(SimpleEditor WIN32 ${editor_src})
target_link_libraries(SimpleEditor LibDXGI LibDirect3D LibCommon windows LibComponents LibHLSL)