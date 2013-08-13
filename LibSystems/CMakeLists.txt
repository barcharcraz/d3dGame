set(system_files
	VelocitySystem3D.h
	VelocitySystem3D.cpp
	MovementController3D.h
	MovementController3D.cpp
	stdafx.h
	stdafx.cpp
	)
add_library(Systems STATIC ${system_files})