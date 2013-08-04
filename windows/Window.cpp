#include "stdafx.h"
#include "Window.h"
#include "Keys.h"
#include <LibInput/Axis.h>
#include <LibInput/DeviceTypes.h>
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
					win->Update();
					
				}
			}
		}
		return msg.wParam;
	}
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		Window * win = (Window*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
		switch (msg) {
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ERASEBKGND:
			break;
		case WM_INPUT:
			win->handleRaw((HRAWINPUT) lparam);
		case WM_KEYDOWN:
			if (input_keymap.count(wparam) && win->_input) {
				win->_input->ActivateKey(input_keymap[wparam]);
			}
			break;
		case WM_KEYUP:
			if (input_keymap.count(wparam) && win->_input) {
				win->_input->DeactivateKey(input_keymap[wparam]);
			}
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
	void Window::Update() {
		update();
		auto dev = _input->Device(Input::MouseType);
		dev->axes[Input::AxisName::X].SetPosition(0.0f);
		dev->axes[Input::AxisName::Y].SetPosition(0.0f);
	}
	void Window::AttachInput(Input::Input* input) {
		_input = input;
		//using namespace std::placeholders;
		//onKeyUp = [input](Input::Keys k){input->DeactivateKey(k); };
		//onKeyDown = [input](Input::Keys k){input->ActivateKey(k); };
	}
	void Window::ClearInput() {
		onKeyUp = nullptr;
		onKeyDown = nullptr;
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
		initRawInput();
		
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
	void Window::initRawInput() {
		RAWINPUTDEVICE Rid;
		Rid.dwFlags = RIDEV_NOLEGACY;
		Rid.hwndTarget = _hwnd;
		Rid.usUsagePage = 0x01;
		Rid.usUsage = 0x02;
		bool result = true;
		result = RegisterRawInputDevices(&Rid, 1, sizeof(Rid));
		if (!result) {
			HRESULT hr = HRESULT_FROM_WIN32(GetLastError());
			throw std::system_error(
				std::error_code(hr, std::system_category()),
				"Raw Input Registration Failed");
		}
	}
	int Window::handleRaw(HRAWINPUT raw) {
		unsigned int size;
		unsigned int errorc;
		GetRawInputData(raw, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER));
		if (size == 0) {
			return 0;
		}
		std::vector<unsigned char> data(size);
		errorc = GetRawInputData(raw, RID_INPUT, data.data(), &size, sizeof(RAWINPUTHEADER));
		if (errorc != size) {
			throw std::runtime_error("raw input read did not return correct size");
		}
		RAWINPUT* praw = (RAWINPUT*) (data.data());
		if (praw->header.dwType == RIM_TYPEMOUSE) {
			long dx = praw->data.mouse.lLastX;
			long dy = praw->data.mouse.lLastY;
			auto device = _input->Device({ 0x01, 0x02 });
			device->axes[Input::AxisName::X].SetPosition(dx);
			device->axes[Input::AxisName::Y].SetPosition(dy);
			
		}
		return 0;
	}
	HWND Window::Hwnd() {
		return _hwnd;
	}

	
}