set(system_files
	AxisAlignedBBSystem.h
	AxisAlignedBBSystem.cpp
	VelocitySystem3D.h
	VelocitySystem3D.cpp
	MovementController3D.h
	MovementController3D.cpp
	CollisionDetectionSystem.h
	CollisionDetectionSystem.cpp
	SimpleCollisionSystem.h
	SimpleCollisionSystem.cpp
	Group.h
	Group.cpp
	stdafx.h
	stdafx.cpp
	)
add_library(Systems STATIC ${system_files})