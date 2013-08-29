set(LibOpenGL_files
	OpenGLRenderer.h
	ModelRenderer.h
	ModelRenderer.cpp
	GLBuffer.h
	GLBuffer.cpp
	GLShader.h
	GLShader.cpp
	stdafx.h
	stdafx.cpp
)
add_library(LibOpenGL STATIC ${LibOpenGL_files})
target_link_libraries(LibOpenGL ${OPEN_gl_LIBRARY} ${GLEW_LIBRARIES})
