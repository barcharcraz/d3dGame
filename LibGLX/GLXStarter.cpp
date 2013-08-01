#include "GLXStarter.h"

namespace LibGLX {
	GLXStarter::GLXStarter ( const xwindows::Window& win ) {
		_winID = win.WinID();
	}

}