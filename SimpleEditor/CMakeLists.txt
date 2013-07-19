set(editor_src
	resource.h
	SimpleEditor.h
	SimpleEditor.cpp
	stdafx.h
	stdafx.cpp
	targetver.h
	)
find_package(FLTK)

add_executable(SimpleEditor ${editor_src})
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(SimpleEditor ${FLTK_LIBRARIES} LibDXGI LibDirect3D LibCommon)