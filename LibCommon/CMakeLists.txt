file(GLOB libcommon_src *.cpp)
file(GLOB libcommon_h *.h)
file(GLOB libcommon_hpp *.hpp)
set(libcommon_files 
	${libcommon_src}
	${libcommon_h}
	${libcommon_hpp}
	)

add_library(LibCommon STATIC ${libcommon_files})
source_group("Header Files\\Components" FILES
	Velocity.hpp
	Transform.hpp
	IComponent.h
	BasicController2D.h
	Camera.h
	Camera.cpp
	)