#include "stdafx.h"
#include "WinLib.h"

//window class
WNDCLASSEX Window::getWindowClass()
{
	return _windowClass;
}
void Window::setWindowClass(WNDCLASSEX newClass)
{
	_windowClass = newClass;
}
//parent
void Window::setParent(HWND newParent) {
	_parent = newParent;
}
HWND Window::getParent() {
	return _parent;
}
//dwExStyle
DWORD Window::getExStyle() {
	return _ExStyle;
}
void Window::setExStyle(DWORD newStyle)
{
	_ExStyle = newStyle;
}
//old style
DWORD Window::getStyle()
{
	return _style;
}
void Window::setStyle(DWORD newStyle)
{
	_style = newStyle;
}
//hwnd
HWND Window::getHwnd()
{
	return _hwnd;
}
void Window::setHwnd(HWND newH)
{
	_hwnd = newH;
}
//x and y
int Window::getX() {
	return _x;
}
int Window::getY() {
	return _y;
}
int Window::getWidth() {
	return _width;
}
int Window::getHeight() {
	return _height;
}
void Window::setX(int newX) {
	_x = newX;
}
void Window::setY(int newY) {
	_y = newY;
}
void Window::setWidth(int newWidth) {
	_width = newWidth;
}
void Window::setHeight(int newHeight) {
	_height = newHeight;
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Register the window with windows
/// 			this will fail silently
/// 			TODO: make this fail with an exception </summary>
///
/// <remarks>	Charlie, 5/2/2012. </remarks>
///-------------------------------------------------------------------------------------------------
ATOM WINAPI Window::LibRegisterWindow() {
	ATOM classAtom;
	classAtom = RegisterClassEx(&(WindowClass));
	if(classAtom == 0) 
	{
		DWORD error = GetLastError();
		return 0;
	} else {
		return classAtom;
	}
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Initialises the window. </summary>
///
/// <remarks>	Charlie, 9/18/2012. </remarks>
///
/// <param name="nCmdShow">   	How to show the window. For
/// 							example SW_SHOWDEFAULT </param>
/// <param name="registerWin">	if true(default) then register the window
/// 							using RegisterClassEx via LibRegisterWindow.
/// 							If false skip this step, note that if you
/// 							dont register the window class and the class
/// 							is not defined someplace else (such as comctrls) then
/// 							CreateWindow will fail. </param>
///-------------------------------------------------------------------------------------------------

void Window::initWindow(int nCmdShow, bool registerWin)
{
	WindowClass = getDefaultClass();
	if(registerWin) {
		LibRegisterWindow();
	}
	Hwnd = LibCreateWindow();
	LibShowWindow(nCmdShow);

}

WNDCLASSEX Window::getDefaultClass() {
	HMODULE mod;
	GetModuleHandleEx(0, NULL, &mod);
	WNDCLASSEX wc;
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbWndExtra = 0; //will only work for windows not for dialoge boxes
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = NULL;
	wc.hInstance = mod;
	wc.lpfnWndProc = wndProcThunk;
	wc.lpszClassName = _name.c_str();
	wc.lpszMenuName = NULL;
	
	return wc;
	
}

HWND WINAPI Window::LibCreateWindow()
{
	HINSTANCE module;
	HWND temp;
	GetModuleHandleEx(0,NULL,&module);
	temp = CreateWindowEx(
		ExStyle,
		_name.c_str(),
		_name.c_str(),
		WndStyle,
		X,
		Y,
		Width,
		Height,
		Parent,
		NULL,
		module,
		NULL
		);
	if(temp == NULL)
	{
		DWORD error;
		LPVOID es;
		error = GetLastError();
		/*FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &es,
			0, NULL );
		*/
		if(true){
			int n = 2;
		};
		return NULL;
	} else {
		SetWindowLongPtr(temp, GWLP_USERDATA, (LONG_PTR)this);
		return temp;
	}
}

void Window::LibShowWindow(int nCmdShow)
{
	ShowWindow(Hwnd, nCmdShow);
	UpdateWindow(Hwnd);
}
WPARAM Window::libStartWindow()
{
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK Window::wndProc(__in HWND hWnd, __in UINT uMsg, __in WPARAM wParam, __in LPARAM lParam) {
	switch(uMsg) {
	case WM_DESTROY:
		if(onDestroy) {
			onDestroy();
			return 0;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
LRESULT CALLBACK Window::wndProcThunk(__in HWND hWnd, __in UINT uMsg, __in WPARAM wParam, __in LPARAM lParam) {
	LONG_PTR lpUserData = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	//check to make sure that lpUser data actually contains a this pointer
	if(lpUserData != 0) {
		Window* member = (Window*)lpUserData;
		
		return member->wndProc(hWnd, uMsg, wParam, lParam);
	}
	//if all else fails fall back on the default window proc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
	
}
Window::Window(){}
Window::Window(LIBSTRING n) : 
	_parent(NULL), 
	_x(0), 
	_y(0),
	_width(0),
	_height(0)
{
	_name = n.c_str();
}
Window::~Window() {}