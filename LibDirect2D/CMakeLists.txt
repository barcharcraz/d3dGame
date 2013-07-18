set(libDirect2d_src
	BitmapLoader.h
	BitmapLoader.cpp
	Conversions.h
	Conversions.cpp
	Direct2DBitmap.h
	Direct2DBitmap.cpp
	Direct2DRectRenderer.h
	Direct2DRectRenderer.cpp
	Direct2DRenderer.h
	Direct2DRenderer.cpp
	Direct2DRenderingMessage.h
	Direct2DRenderingMessage.cpp
	stdafx.h
	stdafx.cpp
	targetver.h
	)
add_library(LibDirect2D ${libDirect2d_src})