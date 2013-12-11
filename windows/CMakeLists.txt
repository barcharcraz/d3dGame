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
	WGLContext.h
	WGLContext.cpp
	)
add_library(windows ${windows_files})
target_link_libraries(windows Input)