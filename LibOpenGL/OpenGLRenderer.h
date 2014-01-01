#ifndef LIBOPENGL_RENDERER_H
#define LIBOPENGL_RENDERER_H
#include "stdafx.h"
#include <windowing.h>
#include <Utils/cache.h>
#include "GLTexture.h"
namespace Image {
    struct ImageData;
}
namespace LibOpenGL {
	class OpenGLRenderer {
	public:
        OpenGLRenderer(windowing::IGLWindow* win);
        OpenGLRenderer();
        ~OpenGLRenderer();
        OpenGLRenderer(const OpenGLRenderer& other) = delete;
        OpenGLRenderer& operator=(const OpenGLRenderer& other) = delete;
        void Present();
        void Clear();

        void Attach(windowing::IGLWindow* target);
        void Detach();
        utils::Cache<Image::ImageData*, GLTexture> TexCache; 
		GLuint ActiveProgram;
    private:
        void init();
        windowing::IGLWindow* _win;
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
