set(windows_files
	Window.h
	Window.cpp
	Keys.h
	Keys.cpp
	stdafx.h
	stdafx.cpp
	WinMain.cpp
	WinMain.h
	ComUtils.h
	ComUtils.cpp
	)
if(USE_OPENGL)
	set(windows_files ${windows_files}
		WGLContext.h
		WGLContext.cpp
		)
endif(USE_OPENGL)
add_library(windows ${windows_files})
target_link_libraries(windows Input)