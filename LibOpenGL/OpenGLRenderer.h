#ifndef LIBOPENGL_RENDERER_H
#define LIBOPENGL_RENDERER_H
#include "stdafx.h"
class GLFWindow;
namespace LibOpenGL {
	class OpenGLRenderer {
	public:
		OpenGLRenderer();
        
		GLuint ActiveProgram;
	};

    //global functions to manipulate the openGL context
    void EnableDepthBuffer();
    void DisableDepthBuffer();
	//! \brief checks for a OpenGL error
	//! and if it finds one throws
	//! an std::system_error
	void CheckError();
}

#endif
