set(app_files
	CrossplatApp.h
	CrossplatApp.cpp
	stdafx.cpp
	stdafx.h
)
add_executable(CrossplatApp ${app_files})
target_link_libraries(CrossplatApp LibXWindows)
