set(libcomponents2d_files
	Rectangle.h
	Rectangle.cpp
	Circle.h
	Circle.cpp
	Line.h
	Line.cpp
	Transform.h
	stdafx.h
	stdafx.cpp
	)
add_library(Components2D STATIC ${libcomponents2d_files})
