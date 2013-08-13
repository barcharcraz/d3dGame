set(effects_files
	stdafx.h
	stdafx.cpp
	EffectsManagement.h
	EffectsManagement.cpp
	Shader.h
	Shader.cpp
	Effect.h
	Effect.cpp
	)
add_library(Effects STATIC ${effects_files})