set(app_files
	CrossplatApp.h
	CrossplatApp.cpp
	stdafx.cpp
	stdafx.h
)
set(app_libs Systems Physics LibComponents LibCommon Image Input AssetLoader Effects Prefabs)
if(USE_DIRECT3D)
set(app_libs ${app_libs} LibDirect3D LibHLSL LibDXGI)
endif()
if(USE_OPENGL)
set(app_libs ${app_libs} LibOpenGL)
endif()
if(USE_GLFW)
set(app_libs ${app_libs} LibGLFW)
endif(USE_GLFW)
if(WIN32)
set(app_libs ${app_libs} windows)
endif()
add_executable(CrossplatApp WIN32 ${app_files})
target_link_libraries(CrossplatApp ${app_libs})
