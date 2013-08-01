#include "stdafx.h"
#include "Window.h"
#include <stdexcept>
namespace xwindows {
	//not in a class
	int Run() {
		XEvent evt;
		while(true) {
			XNextEvent(dpy, &evt);
			switch(evt.type) {
			}
		}
	}

	Window::Window() {
		init(640, 480);
	}
	Window::Window(int w, int h) {
		init(w, h);
	}

	void Window::init(int w, int h) {
		if(!dpy) {
			dpy = XOpenDisplay(nullptr);
		}
		if(dpy == nullptr) {
			throw std::runtime_error("could not open display");
		}
		int WhiteColor = WhitePixel(dpy, DefaultScreen(dpy));
		int BlackColor = BlackPixel(dpy, DefaultScreen(dpy));
		_winxid = XCreateSimpleWindow(dpy,
									  DefaultRootWindow(dpy),
									  0, 0, w, h, 0,
									  BlackColor, WhiteColor);
		XSelectInput(dpy, _winxid, StructureNotifyMask);

	}
	void Window::Show() {
		XMapWindow(dpy, _winxid);
	}
}
