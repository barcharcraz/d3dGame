// SimpleEditor.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "SimpleEditor.h"
#include <Windows.h>
#include <WinLib.h>
#include <CommCtrl.h>
#include <vector>
#include <d2d1helper.h>
#include <LibDirect2D\Direct2DRenderer.h>
#include <LibCommon\Entity.h>
#include <LibCommon\Scene.h>
#include <LibDirect2D\Direct2DRectRenderer.h>
#include <LibDirect2D\Direct2DBitmap.h>
#include <LibCommon/Scene.h>
#include <LibCommon/Transform.hpp>
#include <LibDirect3D\Direct3DRenderer.h>
#include <LibDirect3D\Triangle.h>
#include <LibCommon/ObjFile.h>
#include <LibDirect3D/ModelRenderer.h>
#pragma comment(lib, "LibDirect3D.lib")
#pragma comment(lib,"Comctl32.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "LibDXGI.lib")
#pragma comment(lib, "LibDirect2D.lib")
#pragma comment(lib, "WinLib.lib")

using namespace LibDirect2D;
using namespace LibCommon;
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPTSTR    lpCmdLine,
					 _In_ int       nCmdShow)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwICC = ICC_STANDARD_CLASSES;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
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
	/*
	DWORD initialTime = GetTickCount();
	DWORD dt = 0;

	Lib2DFactory factory(mywin.Hwnd);
	Lib2DDevice device = *factory.createLib2DDevice();
	Lib2DDeviceContext context = *device.getContext();
	Lib2DLinearAnimation anim(0.0,0.0,0.0);
	context.setTarget(factory.getBackBuffer());
	Lib2DBitmap bmp;
	bmp.LoadBitmapFromFile("testBitmap.bmp");
	bmp.BindToRenderTarget(context.getDeviceContext());
	Lib2DBitmapBrush bmpBrush(bmp.getBitmap(),context.getDeviceContext());
	std::vector<ILib2DShape*> commands;
	Lib2DRect rect(D2D1::RectF(0,0,bmp.getBitmap()->GetSize().height,bmp.getBitmap()->GetSize().width),bmpBrush.getBrush(), true);
	Lib2DAnimationManager animShape(&anim, &rect, initialTime);
	commands.push_back(&rect);
	
	mywin.onKeyDown = [&anim, &animShape, &rect](WCHAR key){
		double time = GetTickCount();
		switch (key)
		{
		case VK_LEFT:
			anim = Lib2DLinearAnimation(-50,0,50);
			animShape.resetTime(time);
			break;
		case VK_RIGHT:
			anim = Lib2DLinearAnimation(50,0,50);
			animShape.resetTime(time);
			break;
		case VK_UP:
			anim = Lib2DLinearAnimation(0,-50,50);
			animShape.resetTime(time);
			break;
		case VK_DOWN:
			anim = Lib2DLinearAnimation(0,50,50);
			animShape.resetTime(time);
			break;
		default:
			break;
		}
		
	};
	
	mywin.onNoMessage = [&animShape, &initialTime, &dt, &context, &commands, &factory](){
		double time = GetTickCount();
		animShape.update(time);
		context.Clear();
		context.DrawShapes(commands);
		factory.getSwapChain()->Present(1,0);
		
	};
	*/
	CoInitialize(NULL);
	//Direct3DRenderer d3dRender;
	//CComPtr<ID3D11Debug> pDebug;
	//d3dRender.getDevice()->QueryInterface(IID_PPV_ARGS(&pDebug));
	
	LibDirect3D::Direct3DRenderer * render = new LibDirect3D::Direct3DRenderer(mywin.getHwnd());
	render->addVertexShader("DefaultVS.cso");
	render->addPixelShader("DefaultPS.cso");
	LibCommon::ObjFile modelFile("test.obj");
	Entity * model = new Entity();
	Transform3D * transform = new Transform3D(Eigen::Affine3f::Identity());
	LibDirect3D::ModelRenderer * renderComp = new LibDirect3D::ModelRenderer(modelFile.model());
	model->addComponent(renderComp);
	model->addComponent(transform);
	Scene * sce = new Scene(render);
	sce->AddEntity(model);
	
	//context.DrawShapes(commands);
	//factory.getSwapChain()->Present(1,0);
	mywin.onNoMessage = [&](){
		//render->getContext()->Clear(D2D1::ColorF(D2D1::ColorF::Black));
		
		sce->Update();
		render->Present();
	};
	mywin.libStartWindow();
	delete sce;
	CoUninitialize();
	//pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);

	
	
}