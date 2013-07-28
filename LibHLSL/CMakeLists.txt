set(LibHLSL_files
	HLSLShaderSet.h
	HLSLShaderSet.cpp
	HLSLVertexShader.h
	HLSLVertexShader.cpp
	HLSLPixelShader.h
	HLSLPixelShader.cpp
	stdafx.h
	stdafx.cpp
	)
add_library(LibHLSL STATIC ${LibHLSL_files})