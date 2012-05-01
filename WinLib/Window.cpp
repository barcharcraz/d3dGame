#include "stdafx.h"
#include "WinLib.h"
void Window::LibRegisterWindow() {
}

WNDCLASSEX Window::getDefaultClass() {
	WNDCLASSEX wc;
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0; //will only work for windows not for dialoge boxes
	wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = NULL;
	wc.hInstance = NULL;
	wc.lpfnWndProc = wndProcThunk;
	wc.lpszClassName = name.c_str();
	wc.lpszMenuName = NULL;

	return wc;
	
}
LRESULT CALLBACK Window::wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
LRESULT CALLBACK Window::wndProcThunk(__in HWND hWnd, __in UINT uMsg, __in WPARAM wParam, __in LPARAM lParam) {
	LONG_PTR lpUserData = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	//check to make sure that lpUser data actually contains a this pointer
	if(lpUserData != 0) {
		Window* member = (Window*)lpUserData;
		return member->wndProc(hWnd, uMsg, wParam, lParam);
	} else {
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	
}