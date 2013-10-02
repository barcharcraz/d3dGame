set(app_files
	CrossplatApp.h
	CrossplatApp.cpp
	stdafx.cpp
	stdafx.h
)

IF(USE_DIRECT3D)
add_executable(CrossplatApp WIN32 ${app_files})
target_link_libraries(CrossplatApp windows LibComponents LibCommon Image AssetLoader Effects Prefabs LibDirect3D LibHLSL LibDXGI)
ENDIF(USE_DIRECT3D)
IF(USE_OPENGL)
add_executable(CrossplatApp WIN32 ${app_files})
target_link_libraries(CrossplatApp windows LibGLFW LibOpenGL LibCommon LibComponents Image AssetLoader Effects Prefabs)
ENDIF(USE_OPENGL)