
set(glfw_files
	stdafx.h
	stdafx.cpp
	Window.h
	Window.cpp
    Keys.h
    Keys.cpp
	)
#if we are on windows we need the glfw_native
#code for windows
if(WIN32)
set(glfw_files ${glfw_files} Win32Window.cpp)
endif()
add_library(LibGLFW STATIC ${glfw_files})

target_link_libraries(LibGLFW ${GLFW_LIBRARIES})
