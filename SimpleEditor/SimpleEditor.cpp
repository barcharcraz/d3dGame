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
#include <LibComponents/Effect.h>
#include <LibComponents/Texture.h>
#include <LibComponents/DirectionalLight.h>
#include <LibSystems/MovementController3D.h>
#include <LibSystems/VelocitySystem3D.h>
#include <windowing.h>
#include <LibImage/targa.h>
#include <map>
#include <set>
#include <typeindex>
#include <LibPrefabs/Camera.h>
#include <LibPrefabs/StaticModel.h>
#include <LibPrefabs/DirectionalLight.h>
#include <LibEffects/Effect.h>
#include <LibEffects/Shader.h>
#include <LibEffects/EffectsManagement.h>
#include <LibEffects/EffectCache.h>
#include <Utils/functions.h>

using namespace LibCommon;
using namespace windows;
using namespace Components;
using namespace Systems;
int main(int argc, char** argv)
{
	Input::Input * input = new Input::Input();
	input->AddAction("Left", Input::Keys::A);
	input->AddAction("Right", Input::Keys::D);
	input->AddAction("Forward", Input::Keys::W);
	input->AddAction("Backward", Input::Keys::S);
	input->AddAxisAction("Horizontal", Input::MouseType, Input::AxisName::X);
	input->AddAxisAction("Vertical", Input::MouseType, Input::AxisName::Y);
	
	Window win(1280, 768);
	win.AttachInput(input);
	win.Show();
	
	//Direct3DRenderer d3dRender;
	Image::Targa::TargaFile f = Image::Targa::LoadTarga("Textures/wood_flat/diffuse.tga");

	const std::vector<Effects::ShaderDesc> defaultLayout = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	const std::set<Effects::ShaderCaps> defaultCaps = {
		Effects::ShaderCaps::MESH_INDEXED,
		Effects::ShaderCaps::TEXTURE_MAPPED,
		Effects::ShaderCaps::LIT_DIRECTIONAL
	};
	//CComPtr<ID3D11Debug> pDebug;
	/*utils::Defer<std::function<void()>> def([&](){
		pDebug->ReportLiveDeviceObjects(D3D11_RLDO_FLAGS::D3D11_RLDO_DETAIL);
	});*/
	auto render = std::make_unique<LibDirect3D::Direct3DRenderer>(win.Hwnd());
	
	//render->pDev->QueryInterface(IID_PPV_ARGS(&pDebug));
	
	Effects::EffectCache cache;
	Effects::AddEffect({ "DefaultVS.cso", "DefaultPS.cso", defaultLayout, defaultCaps });
	LibDirect3D::Direct3DTexture d3dTex{ Image::ImageData(f) };
	LibCommon::ObjFile modelFile("TestObj.obj");
	LibCommon::ObjFile cone("Cone.obj");
	Prefabs::Camera * cam = new Prefabs::Camera();
	Prefabs::StaticModel * model = new Prefabs::StaticModel(modelFile.model(), Texture(&d3dTex));
	Prefabs::StaticModel * coneMod = new Prefabs::StaticModel(cone.model(), Texture(&d3dTex));
	model->Get<Transform3D>()->transform.translate(Eigen::Vector3f{ 0, 0, -10 });
	model->AddComponent<Components::Velocity3D>(Eigen::Affine3f(Eigen::AngleAxisf(0.01f, Eigen::Vector3f::UnitY()) * Eigen::Affine3f::Identity()));
	coneMod->AddComponent<Components::Velocity3D>(Eigen::Affine3f(Eigen::AngleAxisf(0.01f, Eigen::Vector3f::UnitX()) * Eigen::Affine3f::Identity()));
	MovementController3D * control = new MovementController3D();
	VelocitySystem3D * velsys = new VelocitySystem3D();
	
	cam->AddComponent(input);
	LibDirect3D::ModelRenderer * renderComp = new LibDirect3D::ModelRenderer(*render);
	auto sce = std::make_unique<Scene>();
	sce->AddSystem(renderComp);
	sce->AddSystem(control);
	sce->AddEntity(model);
	sce->AddEntity(coneMod);
	sce->AddEntity(cam);
	sce->AddEntity(std::make_unique<Prefabs::DirectionalLight>(Eigen::Vector4f{ 0.70f, 0.0f, 0.20f, 1.0f }, Eigen::Vector3f{ 0.0f, 0.0f, -100.0f }));
	sce->AddSystem(velsys);
	//context.DrawShapes(commands);
	//factory.getSwapChain()->Present(1,0);
	
	win.update = [&]() {
		render->Clear();
		sce->Update();
		render->Present();
		
		
	};
	
	
	auto rv = Run();

	
	return rv;
	
	
	
}