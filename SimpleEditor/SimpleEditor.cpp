// SimpleEditor.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SimpleEditor.h"
#include <WinLib.h>
#include <CommCtrl.h>
#include <d2d1_1.h>
#include <Lib2DDevice.h>
#include <Lib2DFactory.h>
#include <Lib2DFactory.h>
//#pragma comment(lib,"Lib3D.lib")
#pragma comment(lib,"Comctl32.lib")
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwICC = ICC_STANDARD_CLASSES;
	InitCommonControlsEx(&icex);
	
	LIBSTRING name(L"test");
	Window mywin(name);
	mywin.X=0;
	mywin.Y=0;
	mywin.Width=640;
	mywin.Height=480;
	mywin.ExStyle = WS_EX_CLIENTEDGE;
	mywin.WndStyle = WS_OVERLAPPEDWINDOW;
	mywin.initWindow(SW_SHOWNORMAL);
	mywin.onDestroy = [](){PostQuitMessage(0);};
	/*
	Device device(mywin.Hwnd);
	
	float color[4];
	color[0]=255.0f;
	color[1]=0.0f;
	color[2]=0.0f;
	color[3]=1.0f;
	
	device.d3dDeviceContext->ClearRenderTargetView(device.pRenderTargetView,color);
	device.swapChain->Present(0,0);
	*/
	Lib2DFactory factory(mywin.Hwnd);
	Lib2DDevice * device = factory.createLib2DDevice().get();
	Lib2DDeviceContext * context = device->getContext().get();


	mywin.libStartWindow();
	
	
	
}