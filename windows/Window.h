#pragma once
#include "stdafx.h"
#include <LibInput/Keys.h>
#include <LibInput/Input.h>
namespace windows {
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	int Run();

	class Window {
		friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	public:
		Window();
		Window(int w, int h);
		HWND Hwnd();
		HWND Handle();
		void Show();
		void AttachInput(Input::Input* input);
		void ClearInput();
		void Update();
		std::function<void(Input::Keys)> onKeyDown;
		std::function<void(Input::Keys)> onKeyUp;
		std::function<void(long dx, long dy)> onMouseMove;
		std::function<void()> update;
	private:
		void init(int w, int h);
		void initDefault();
		void initRawInput();
		int handleRaw(HRAWINPUT raw);
		WNDCLASSEX _class;
		HWND _hwnd;
		Input::Input* _input;
	};
	

}