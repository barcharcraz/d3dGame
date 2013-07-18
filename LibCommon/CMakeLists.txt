set(libcommon_src
	Entity.cpp
	Input.cpp
	Camera.cpp
	InputMessage.cpp
	KeyDownMessage.cpp
	KeyUpMessage.cpp
	UpdateMessage.cpp
	Bubbly.cpp
	ObjFile.cpp
	Scene.cpp
	stdafx.cpp
	)
add_library(LibCommon SHARED ${libcommon_src})