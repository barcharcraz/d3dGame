#ifndef LIBOPENGL_RENDERER_H
#define LIBOPENGL_RENDERER_H

namespace LibOpenGL {
	class OpenGLRenderer {
	public:
		//! \brief this function is for creating an
		//! open gl context in X windows. you shoudl pass
		//! an Xwindows Window to this function, also
		//! known as an XID
		OpenGLRenderer(unsigned long xid);
		//! \brief this function is for createing an openGL
		//! context on windows, you should pass a handle to 
		//! a device context to this function
		OpenGLRenderer(void* hDC);
	}
}

#endif