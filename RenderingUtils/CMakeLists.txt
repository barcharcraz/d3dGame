set(renderingutils_files
	ModelProcessing.cpp
	ModelProcessing.h
	EntityFunctions.h
	EntityFunctions.cpp
	TextureFunctions.h
	TextureFunctions.cpp
	)
add_library(RenderingUtils STATIC ${renderingutils_files})