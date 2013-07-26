// SimpleEditor.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "SimpleEditor.h"
#include <Windows.h>
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
#include <LibCommon/Velocity.hpp>
#include <LibCommon/Camera.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <windows/Window.h>
#include <map>
#include <typeindex>

using namespace LibDirect2D;
using namespace LibCommon;
using namespace windows;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrvInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	Window win(640, 480);
	win.Show();
	
	
	CoInitialize(NULL);
	//Direct3DRenderer d3dRender;
	//CComPtr<ID3D11Debug> pDebug;
	//d3dRender.getDevice()->QueryInterface(IID_PPV_ARGS(&pDebug));
	
	LibDirect3D::Direct3DRenderer * render = new LibDirect3D::Direct3DRenderer(win.Hwnd());
	render->addVertexShader("DefaultVS.cso");
	render->addPixelShader("DefaultPS.cso");
	LibCommon::ObjFile modelFile("Torus.obj");
	Entity * model = new Entity();
	Entity * camera = new Entity();
	Transform3D * transform = new Transform3D(Eigen::Translation3f(0, 0, -10));
	Velocity3D * vel = new Velocity3D(Eigen::AngleAxisf(0.2f, Eigen::Vector3f::UnitX()));
	Transform3D * camPos = new Transform3D(Eigen::Affine3f::Identity());
	Camera * cam = new Camera();
	camera->AddComponent(cam);
	camera->AddComponent(camPos);
	LibDirect3D::ModelRenderer * renderComp = new LibDirect3D::ModelRenderer(modelFile.model());
	model->AddComponent(renderComp);
	model->AddComponent(transform);
	model->AddComponent(vel);
	Scene * sce = new Scene(render);
	sce->AddEntity(model);
	sce->AddEntity(camera);
	//context.DrawShapes(commands);
	//factory.getSwapChain()->Present(1,0);
	
	win.update = [&]() {
		
		sce->Update();
		render->Present();
		render->Clear();
		
	};
	//pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	
	int rv = Run();

	delete sce;
	CoUninitialize();
	return rv;
	
	
	
}