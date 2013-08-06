#ifndef LIBXWINDOWS_WINDOW_H
#define LIBXWINDOWS_WINDOW_H
#include "stdafx.h"
#include <X11/Xlib.h>
#include <functional>
#include <memory>
namespace xwindows {
	static Display* dpy;
	//! \brief Run starts the program's
	//!	       main loop and dispatches events
	//!        to stored message callbacks
	int Run();
	//! \brief a window for XWindows
	//!        the interface for the XWindows
	//!        window is almost exactly the same
	//!        as the one for the winAPI window
	class Window {
	public:
		//! \brief constructs a window
		//!        with a requested size of
		//!        640x480
		Window();
		Window(int w, int h);
		XID WinID() const;
		void Show();
		std::function<void()> update;
	private:
		void init(int w, int h);
		XID _winxid;

	};
}
#endif
