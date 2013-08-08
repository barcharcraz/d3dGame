#ifndef LIBGLX_GLXSTARTER_H
#define LIBGLX_GLXSTARTER_H
#include <GL/glx.h>
#include <GL/gl.h>
#include <X11/Xlib.h>
//we are including the xwindows window
//directly since that is really the window that we want
//GLX already depends on X anyways
#include <LibXWindows/Window.h>
namespace LibGLX {
	class GLXStarter {
		GLXStarter(const xwindows::Window& win);
		GLXStarter(const xwindows::Window* win);
		GLXStarter(Display* dpy, XID win, XID root);
		GLXStarter(Display* dpy, XID win);
		void init(Display* dpy, XID win, XID root);
	private:
		void initFBConfig();

		XID _winID;
		XID _rootID;
		Display* _dpy;
		GLXFBConfig* _fbConfig;
	};
}

#endif
