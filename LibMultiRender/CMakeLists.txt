set(multirender_files
	MultiRenderSystem.h
	MultiRenderSystem.cpp
	)
add_library(MultiRender STATIC ${multirender_files})
target_link_libraries(MultiRender LibDirect3D LibOpenGL LibCommon)