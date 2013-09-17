set(app_files
	CrossplatApp.h
	CrossplatApp.cpp
	stdafx.cpp
	stdafx.h
)

IF(HAS_WIN32)
add_executable(CrossplatApp WIN32 ${app_files})
target_link_libraries(CrossplatApp windows LibComponents LibCommon Image AssetLoader Effects Prefabs LibDirect3D LibHLSL LibDXGI)
ENDIF(HAS_WIN32)
IF(GLFW3_FOUND)
add_executable(CrossplatApp ${app_files})
target_link_libraries(CrossplatApp LibGLFW LibOpenGL LibCommon LibComponents Image AssetLoader Effects Prefabs)
ENDIF(GLFW3_FOUND)