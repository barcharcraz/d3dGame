#include <functional>
#include <iostream>
#include "MacroUtils.h"
#include "stdafx.h"
#include <Property.h>
#pragma once



// This class is exported from the WinLib.dll
class WINLIB_API CWinLib {
public:
	CWinLib(void);
	// TODO: add your methods here.
};

class WINLIB_API Window {
public:
	Window();
	Window(LIBSTRING name);
	~Window();
	void initWindow(int nCmdShow, bool registerWin=true);
	WPARAM libStartWindow();
	ATOM WINAPI LibRegisterWindow();
	HWND WINAPI LibCreateWindow();
	void LibShowWindow(int nCmdShow);
#pragma region Properties
	__declspec(property(put=setWindowClass, get=getWindowClass) ) WNDCLASSEX WindowClass;
	__declspec(property(put=setExStyle, get=getExStyle) ) DWORD ExStyle;
	__declspec(property(put=setStyle, get=getStyle) ) DWORD WndStyle;
	__declspec(property(put=setHwnd, get=getHwnd) ) HWND Hwnd;
	__declspec(property(put=setParent, get=getParent) ) HWND Parent;
	__declspec(property(put=setX, get=getX) ) int X;
	__declspec(property(put=setY, get=getY) ) int Y;
	__declspec(property(put=setWidth, get=getWidth) ) int Width;
	__declspec(property(put=setHeight, get=getHeight) ) int Height;
	
	
#pragma endregion

#pragma region messagehandlers
	std::function<void()> onDestroy;
	std::function<void(WCHAR)> onKeyDown;
	std::function<void()> onNoMessage;
#pragma endregion

#pragma region accessors
	//window class
	WNDCLASSEX getWindowClass();
	void setWindowClass(WNDCLASSEX newClass);
	//parent
	void setParent(HWND newParent);
	HWND getParent();
	//dwExStyle
	DWORD getExStyle();
	void setExStyle(DWORD newStyle);
	//old style
	DWORD getStyle();
	void setStyle(DWORD newStyle);
	//hwnd
	HWND getHwnd();
	void setHwnd(HWND newH);
	//x and y
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	void setX(int newX);
	void setY(int newY);
	void setWidth(int newWidth);
	void setHeight(int newHeight);

#pragma endregion
protected:
	WNDCLASSEX getDefaultClass();
	//the default window proc that dispatches messages to appropriate handlers, set via lambda and can be overridden <3 C++0x
	virtual LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	LIBSTRING _name;
	WNDCLASSEX _windowClass;
	DWORD _ExStyle;
	DWORD _style;
	HWND _parent;
	HWND _hwnd;
	int _x;
	int _y;
	int _width;
	int _height;
	static LRESULT CALLBACK wndProcThunk(__in HWND hWnd, __in UINT uMsg, __in WPARAM wParam, __in LPARAM lParam);
	
};

extern WINLIB_API int nWinLib;

WINLIB_API int fnWinLib(void);
