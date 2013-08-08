set(prefab_files
	stdafx.h
	stdafx.cpp
	Camera.h
	Camera.cpp
	)
add_library(Prefabs STATIC ${prefab_files})
target_link_libraries(Prefabs LibComponents)