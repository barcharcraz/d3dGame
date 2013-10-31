#ifndef LIBOPENGL_RENDERER_H
#define LIBOPENGL_RENDERER_H
#include "stdafx.h"
#include <windowing.h>
namespace LibOpenGL {
	class OpenGLRenderer {
	public:
        OpenGLRenderer(windowing::IWindow* win);
        
        void Present();
        void Clear();

		GLuint ActiveProgram;
    private:
        void init();
        windowing::IWindow* _win;
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
