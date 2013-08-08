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
#include <LibDirect3D/Direct3DTexture.h>
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
#include <LibComponents/Texture.h>
#include <LibSystems/MovementController3D.h>
#include <LibSystems/VelocitySystem3D.h>
#include <windowing.h>
#include <LibImage/targa.h>
#include <map>
#include <typeindex>
#include <LibPrefabs/Camera.h>


using namespace LibCommon;
using namespace windows;
using namespace Components;
using namespace Systems;
int main(int argc, char** argv)
{
	Window win(640, 480);
	win.Show();
	
	
	ComInitialize com;
	//Direct3DRenderer d3dRender;
	Image::Targa::TargaFile f = Image::Targa::LoadTarga("Textures/wood_flat/diffuse.tga");

	const std::vector<D3D11_INPUT_ELEMENT_DESC> defaultLayout = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	LibDirect3D::Direct3DRenderer * render = new LibDirect3D::Direct3DRenderer(win.Hwnd());
	//CComPtr<ID3D11Debug> pDebug;
	//render->m_pDevice->QueryInterface(IID_PPV_ARGS(&pDebug));
	LibShaders::HLSLPixelShader ps("DefaultPS.cso");
	LibShaders::HLSLVertexShader vs("DefaultVS.cso", defaultLayout);
	auto shaders = std::make_unique<LibShaders::HLSLShaderSet>(vs, ps);
	LibDirect3D::Direct3DTexture d3dTex{ Image::ImageData(f) };
	LibCommon::ObjFile modelFile("TestObj.obj");
	Entity * model = new Entity();
	Prefabs::Camera * cam = new Prefabs::Camera();
	Transform3D * transform = new Transform3D(Eigen::Affine3f(Eigen::Translation3f(0, 0, -10)));
	Model * mod = new Model(modelFile.verts(), modelFile.indices());
	Texture * tex = new Texture(&d3dTex);
	MovementController3D * control = new MovementController3D();
	VelocitySystem3D * velsys = new VelocitySystem3D();
	Input::Input * input = new Input::Input();
	input->AddAction("Left", Input::Keys::A );
	input->AddAction("Right", Input::Keys::D);
	input->AddAction("Forward", Input::Keys::W);
	input->AddAction("Backward", Input::Keys::S);
	input->AddAxisAction("Horizontal", Input::MouseType, Input::AxisName::X);
	input->AddAxisAction("Vertical", Input::MouseType, Input::AxisName::Y);
	win.AttachInput(input);
	Shaders * shadersComp = new Shaders(shaders.get());
	cam->AddComponent(input);
	LibDirect3D::ModelRenderer * renderComp = new LibDirect3D::ModelRenderer(*render);
	model->AddComponent(transform);
	model->AddComponent(mod);
	model->AddComponent(shadersComp);
	model->AddComponent(tex);
	Scene * sce = new Scene(render);
	sce->AddSystem(renderComp);
	sce->AddSystem(control);
	sce->AddEntity(model);
	sce->AddEntity(cam);
	sce->AddSystem(velsys);
	//context.DrawShapes(commands);
	//factory.getSwapChain()->Present(1,0);
	
	win.update = [&]() {
		render->Clear();
		sce->Update();
		render->Present();
		
		
	};
	
	
	auto rv = Run();

	delete sce;
	//pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	return rv;
	
	
	
}