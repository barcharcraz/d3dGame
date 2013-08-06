set(libd3d_src
	Buffers.h
	Buffers.cpp
	Direct3DRenderer.h
	Direct3DRenderer.cpp
	ModelRenderer.h
	ModelRenderer.cpp
	DataFormats.h
	Direct3DTexture.h
	Direct3DTexture.cpp
	stdafx.h
	stdafx.cpp
	targetver.h
	)
add_library(LibDirect3D STATIC ${libd3d_src})