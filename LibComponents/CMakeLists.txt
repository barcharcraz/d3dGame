set(libcomponents_files 
	Transform.h
	Model.h
	Velocity.h
	Camera.h
	Camera.cpp
	IComponent.h
	Shaders.h
	Shaders.cpp
	Texture.h
	Texture.cpp
	stdafx.h
	stdafx.cpp
	)

add_library(LibComponents STATIC ${libcomponents_files})