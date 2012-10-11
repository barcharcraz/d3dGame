// SimpleEditor.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SimpleEditor.h"
#include <WinLib.h>
#include <CommCtrl.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <Lib2DDevice.h>
#include <Lib2DFactory.h>
#include <Lib2DFactory.h>
#include <Lib2DRect.h>
#include <vector>
//#pragma comment(lib,"Lib3D.lib")
#pragma comment(lib,"Comctl32.lib")
#include <d2d1helper.h>
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
	Lib2DDevice device = *factory.createLib2DDevice();
	Lib2DDeviceContext context = *device.getContext();
	context.setTarget(factory.getBackBuffer());
	using namespace D2D1;
	CComPtr<ID2D1SolidColorBrush> blackBrush;
	
	blackBrush = context.GetSolidColorBrush(D2D1::ColorF::Blue);
	
	std::vector<ILib2DShape*> commands;
	Lib2DRect rect(RectF(0.0,0.0,100.0,100.0),blackBrush, true);
	commands.push_back(&rect);
	mywin.onKeyDown = [rect](WCHAR key){
		switch (key)
		{
		case VK_LEFT:
			
		default:
			break;
		}
	}
	context.DrawShapes(commands);
	factory.getSwapChain()->Present(1,0);
	mywin.libStartWindow();
	
	
	
}