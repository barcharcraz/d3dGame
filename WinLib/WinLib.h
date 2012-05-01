#include <functional>
#include <iostream>
#include "MacroUtils.h"
#include "stdafx.h"
#pragma once



// This class is exported from the WinLib.dll
class WINLIB_API CWinLib {
public:
	CWinLib(void);
	// TODO: add your methods here.
};

class Window {
public:
	Window();
	Window(LIBSTRING name);
	~Window();
protected:
	WNDCLASSEX getDefaultClass();
	//the default window proc that dispatches messages to appropriate handlers, set via lambda and can be overridden <3 C++0x
	virtual LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	LIBSTRING name;
	WNDCLASSEX windowClass;
	static LRESULT CALLBACK wndProcThunk(__in HWND hWnd, __in UINT uMsg, __in WPARAM wParam, __in LPARAM lParam);
	void LibRegisterWindow();
	void LibCreateWindow();
	void LibShowWindow();
};

extern WINLIB_API int nWinLib;

WINLIB_API int fnWinLib(void);
