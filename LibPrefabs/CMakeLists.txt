set(prefab_files
	stdafx.h
	stdafx.cpp
	Camera.h
	Camera.cpp
	StaticModel.h
	StaticModel.cpp
	DirectionalLight.h
	DirectionalLight.cpp
	)
add_library(Prefabs STATIC ${prefab_files})
target_link_libraries(Prefabs LibComponents Effects)