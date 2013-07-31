set(app_files
	CrossplatApp.h
	CrossplatApp.cpp
	stdafx.cpp
	stdafx.h
)

IF(HAS_WIN32)
add_executable(CrossplatApp WIN32 ${app_files})
target_link_libraries(CrossplatApp windows)
ENDIF(HAS_WIN32)
IF(HAS_X11)
add_executable(CrossplatApp ${app_files})
target_link_libraries(CrossplatApp LibXWindows)
ENDIF(HAS_X11)