// SimpleEditor.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "SimpleEditor.h"
#include <Windows.h>
#include <vector>
#include <LibCommon\Entity.h>
#include <LibCommon\Scene.h>
#include <LibCommon/Scene.h>
#include <LibDirect3D\Direct3DRenderer.h>
#include <LibCommon/ObjFile.h>
#include <LibDirect3D/ModelRenderer.h>
#include <LibHLSL/HLSLShaderSet.h>
#include <LibHLSL/HLSLVertexShader.h>
#include <LibHLSL/HLSLPixelShader.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <LibComponents/Camera.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Velocity.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Model.h>
#include <LibComponents/Shaders.h>
#include <windowing.h>
#include <map>
#include <typeindex>


using namespace LibCommon;
using namespace windows;
using namespace Components;
int main(int argc, char** argv)
{
	Window win(640, 480);
	win.Show();
	
	
	ComInitialize com;
	//Direct3DRenderer d3dRender;
	//CComPtr<ID3D11Debug> pDebug;
	//d3dRender.getDevice()->QueryInterface(IID_PPV_ARGS(&pDebug));
	const std::vector<D3D11_INPUT_ELEMENT_DESC> defaultLayout = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	LibDirect3D::Direct3DRenderer * render = new LibDirect3D::Direct3DRenderer(win.Hwnd());

	LibShaders::HLSLPixelShader ps("DefaultPS.cso");
	LibShaders::HLSLVertexShader vs("DefaultVS.cso", defaultLayout);
	auto shaders = std::make_unique<LibShaders::HLSLShaderSet>(vs, ps);

	LibCommon::ObjFile modelFile("Torus.obj");
	Entity * model = new Entity();
	Entity * camera = new Entity();
	Transform3D * transform = new Transform3D(Eigen::Affine3f(Eigen::Translation3f(0, 0, -10)));
	Velocity3D * vel = new Velocity3D(Eigen::Affine3f(Eigen::AngleAxisf(0.2f, Eigen::Vector3f::UnitX())));
	Transform3D * camPos = new Transform3D(Eigen::Affine3f::Identity());
	Camera * cam = new Camera();
	Model * mod = new Model(modelFile.verts(), modelFile.indices());
	Shaders * shadersComp = new Shaders(shaders.get());
	camera->AddComponent(cam);
	camera->AddComponent(camPos);
	LibDirect3D::ModelRenderer * renderComp = new LibDirect3D::ModelRenderer(*render);
	model->AddComponent(transform);
	model->AddComponent(vel);
	model->AddComponent(mod);
	model->AddComponent(shadersComp);
	Scene * sce = new Scene(render);
	sce->AddSystem(renderComp);
	sce->AddEntity(model);
	sce->AddEntity(camera);
	//context.DrawShapes(commands);
	//factory.getSwapChain()->Present(1,0);
	
	win.update = [&]() {
		render->Clear();
		sce->Update();
		render->Present();
		
		
	};
	//pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	
	auto rv = Run();

	delete sce;
	return rv;
	
	
	
}