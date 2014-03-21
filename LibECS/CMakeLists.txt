set(ecs_files
	Scene.h
	Scene.cpp
	Row.h
	Row.cpp
	Component.h
	Component.cpp
	System.h
	System.cpp
	World.h
	World.cpp
	)
add_library(sparse_ecs STATIC ${ecs_files})
target_include_directories(sparse_ecs INTERFACE ..)