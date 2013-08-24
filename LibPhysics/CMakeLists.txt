set(libPhysics_src
	SweepAndPrune.h
	SweepAndPrune.cpp
	)
add_library(Physics STATIC ${libPhysics_src})