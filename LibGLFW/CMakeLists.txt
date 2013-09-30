
set(glfw_files
	stdafx.h
	stdafx.cpp
	Window.h
	Window.cpp
    Keys.h
    Keys.cpp
	)
add_library(LibGLFW STATIC ${glfw_files})
target_link_libraries(LibGLFW ${GLFW3_LIBRARY})
