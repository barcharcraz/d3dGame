set(LibOpenGL_files
	OpenGLRenderer.h
	GLModelRenderer.h
	GLModelRenderer.cpp
	GLBuffer.h
	GLBuffer.cpp
	GLShader.h
	GLShader.cpp
	GLProgram.h
	GLProgram.cpp
	GLAttribArray.h
	GLAttribArray.cpp
	stdafx.h
	stdafx.cpp
)
add_library(LibOpenGL STATIC ${LibOpenGL_files})
target_link_libraries(LibOpenGL ${OPEN_gl_LIBRARY} ${GLEW_LIBRARIES})
