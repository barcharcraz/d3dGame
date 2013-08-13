file(GLOB libcommon_src *.cpp)
file(GLOB libcommon_h *.h)
file(GLOB libcommon_hpp *.hpp)
set(libcommon_files 
	${libcommon_src}
	${libcommon_h}
	${libcommon_hpp}
	)

add_library(LibCommon STATIC ${libcommon_files})
source_group("Header Files\\Components\\Entities" FILES
	Entity.h
	Scene.h
	)
source_group("Source Files\\Components\\Entities" FILES
	Entity.cpp
	Scene.cpp
	)
source_group("Header Files\\Messages" FILES
	IMessage.h
	Bubbly.h
	Get.hpp
	Markers.h
	UpdateMessage.h
	IRenderingMessage.h
	)
source_group("Source Files\\Messages" FILES
	Bubbly.cpp
	UpdateMessage.cpp
	)
source_group("Header Files\\Systems" FILES
	System.h
	)
source_group("Source Files\\Systems" FILES
	System.cpp
	)

