#include "stdafx.h"
#include "Window.h"

namespace windows {
	//----NON CLASS---------
	size_t Run() {
		MSG msg{ 0 };
		while (msg.message != WM_QUIT) {
			Window * win = (Window*) GetWindowLongPtr(msg.hwnd, GWLP_USERDATA);
			if (win == nullptr || win->update == nullptr) {
				if (GetMessage(&msg, nullptr, 0, 0) > 0) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else {
				if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else {
					win->update();
				}
			}
		}
		return msg.wParam;
	}
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		switch (msg) {
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ERASEBKGND:
			break;
		default:
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}
		return 0;
	}


	Window::Window(int w, int h) {
		initDefault();
		
		init(w,h);
	}
	Window::Window() {
		initDefault();
		init(640, 480);
	}
	void Window::Show() {
		ShowWindow(_hwnd, SW_SHOWDEFAULT);
		UpdateWindow(_hwnd);
		
	}
	//-----------PRIVATE-------------------
	void Window::init(int w, int h) {
		_hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"Windowing",
			L"DirectX11.1 window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			w, h, nullptr, nullptr, GetModuleHandle(0), nullptr
			);
		if (_hwnd == NULL) {
			throw std::exception("failed to create window");
		}
		SetWindowLongPtr(_hwnd, GWLP_USERDATA, (LONG_PTR)this);
		
	}
	void Window::initDefault() {
		_class.cbSize = sizeof(WNDCLASSEX);
		_class.style = 0;
		_class.lpfnWndProc = WndProc;
		_class.hInstance = GetModuleHandle(0);
		_class.cbClsExtra = 0;
		_class.cbWndExtra = 0;
		_class.hIcon = nullptr;
		_class.hCursor = nullptr;
		_class.hIconSm = nullptr;
		_class.hbrBackground = nullptr;
		_class.lpszMenuName = nullptr;
		_class.lpszClassName = L"Windowing";
		auto registerResult = RegisterClassEx(&_class);
		if (!registerResult) {
			throw registerResult;
		}
	}
	HWND Window::Hwnd() {
		return _hwnd;
	}

	
}