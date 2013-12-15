set(ecs_files
	Scene.h
	Scene.cpp
	Row.h
	Row.cpp
	Component.h
	Component.cpp
	)
add_library(sparse_ecs STATIC ${ecs_files})