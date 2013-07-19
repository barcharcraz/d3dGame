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
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/x.H>


using namespace LibDirect2D;
using namespace LibCommon;
int main(int argc, char** argv)
{
	Fl_Window win(640, 480);
	win.end();
	win.show(argc, argv);
	HWND wnd = fl_xid(&win);
	
	CoInitialize(NULL);
	//Direct3DRenderer d3dRender;
	//CComPtr<ID3D11Debug> pDebug;
	//d3dRender.getDevice()->QueryInterface(IID_PPV_ARGS(&pDebug));
	
	LibDirect3D::Direct3DRenderer * render = new LibDirect3D::Direct3DRenderer(wnd);
	render->addVertexShader("DefaultVS.cso");
	render->addPixelShader("DefaultPS.cso");
	LibCommon::ObjFile modelFile("test.obj");
	Entity * model = new Entity();
	//Velocity3D * vel = new Velocity3D(Eigen::AngleAxisf(0.2f, Eigen::Vector3f::UnitX()));
	Transform3D * transform = new Transform3D(Eigen::Scaling(0.1f));
	
	LibDirect3D::ModelRenderer * renderComp = new LibDirect3D::ModelRenderer(modelFile.model());
	model->addComponent(renderComp);
	model->addComponent(transform);
	//model->addComponent(vel);
	Scene * sce = new Scene(render);
	sce->AddEntity(model);
	//context.DrawShapes(commands);
	//factory.getSwapChain()->Present(1,0);
	
	
	//pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	
	return Fl::run();

	delete sce;
	CoUninitialize();
	
}