set(prefab_files
	stdafx.h
	stdafx.cpp
	Camera.h
	Camera.cpp
	StaticModel.h
	StaticModel.cpp
	)
add_library(Prefabs STATIC ${prefab_files})
target_link_libraries(Prefabs LibComponents)