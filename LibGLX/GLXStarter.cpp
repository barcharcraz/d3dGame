#include "GLXStarter.h"
#include <stdexcept>
namespace LibGLX {
	static GLXFBConfig findBestConfig(GLXFBConfig* configc, int numConfigs);
	GLXStarter::GLXStarter ( const xwindows::Window& win ) {
		_winID = win.WinID();
	}
	void GLXStarter::init(Display *dpy, XID win, XID root) {

	}
	void GLXStarter::initFBConfig() {
		int visualAttr[] = {
			GLX_X_RENDERABLE, True,
			GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_RENDER_TYPE, GLX_RGBA_BIT,
			GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
			GLX_RED_SIZE, 8,
			GLX_GREEN_SIZE, 8,
			GLX_BLUE_SIZE, 8,
			GLX_ALPHA_SIZE, 8,
			GLX_DEPTH_SIZE, 24,
			GLX_STENCIL_SIZE, 8,
			GLX_DOUBLEBUFFER, True,
			None
		};
		int glxmajor;
		int glxminor;
		int err = glXQueryVersion(_dpy, &glxmajor, &glxminor);
		if(!err) {
			throw std::runtime_error("could not query the GLX version");
		}
		if(glxmajor == 1 && glxminor < 3) {
			throw std::runtime_error("OpenGL rendering requires a minimum of GLX version 1.3");
		}
		int fbcount;
		GLXFBConfig *fbcs = glXChooseFBConfig(_dpy, DefaultScreen(_dpy), visualAttr, &fbcount);
		if(!fbcs) {
			throw std::runtime_error("could not choose FB configs");
		}
		//int best_fbc = -1;
		//int worst_fbc = -1;

	}

	/* ---static helpers----- */
	GLXFBConfig findBestConfig(GLXFBConfig *configc, int numConfigs) {
		//int best_fbc = -1;
		//int worst_fbc = -1;

	}


}
