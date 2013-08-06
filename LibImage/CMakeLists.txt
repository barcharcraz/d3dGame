set(libimage_files
	stdafx.h
	stdafx.cpp
	targa.h
	targa.cpp
	conversions.h
	conversions.cpp
	image.h
	)
add_library(Image STATIC ${libimage_files})