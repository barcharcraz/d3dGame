set(libprefabs2d_files
	Crosshair.h
	Crosshair.cpp
	)
add_library(Prefabs2D STATIC ${libprefabs2d_files})
target_link_libraries(Prefabs2D Components2D)