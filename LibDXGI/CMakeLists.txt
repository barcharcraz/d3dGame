set(libdxgi_src
	LibDXGI.h
	LibDXGI.cpp
	stdafx.h
	stdafx.cpp
	targetver.h
	)
add_library(LibDXGI STATIC ${libdxgi_src})