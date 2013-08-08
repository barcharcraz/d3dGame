find_package(GLFW3)
set(glfw_files
	stdafx.h
	stdafx.cpp
	Window.h
	Window.cpp
	)
if(GLFW3_FOUND)
	include_directories(${GLFW3_INCLUDE_PATH})
	add_library(LibGLFW STATIC ${glfw_files})
	target_link_libraries(LibGLFW ${GLFW3_LIBRARY})
ENDIF(GLFW3_FOUND)