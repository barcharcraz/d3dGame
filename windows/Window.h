#pragma once
#include "stdafx.h"
namespace windows {
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	int Run();

	class Window {
	public:
		Window();
		Window(int w, int h);
		HWND Hwnd();
		void Show();
		std::function<void()> update;
	private:
		void init();
		void initDefault();
		
		WNDCLASSEX _class;
		HWND _hwnd;
	};
	

}