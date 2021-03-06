#include "stdafx.h"
#include "ModelRenderer.h"
#include "Direct3DTexture.h"
#include "Buffers.h"
#include "ShaderResource.h"
#include <LibCommon/Data.h>
#include <LibComponents/Model.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Camera.h>
#include <LibCommon/Scene.h>
#include <LibComponents/Texture.h>
#include <LibHLSL/HLSLShaderSet.h>
#include <LibHLSL/HLSLPixelShader.h>
#include <LibHLSL/HLSLVertexShader.h>
#include <LibComponents/Effect.h>
#include <LibComponents/Material.h>
#include <LibComponents/PointLight.h>
#include <LibHLSL/HLSLCache.h>
#include <cstddef>
namespace LibDirect3D {
	ModelRenderer::ModelRenderer(Direct3DRenderer* renderer)
		: System({ typeid(Components::Model), typeid(Components::Transform3D), typeid(Components::Material), typeid(Components::Effect) }), 
		render(renderer)
	{
		
	}
	void ModelRenderer::PreProcess() {
		auto camera = parent->SelectEntity({ typeid(Components::Camera), typeid(Components::Transform3D) });
		directionalLights = parent->SelectComponents<Components::DirectionalLight>();
		//_lights = render->CreateConstantBuffer(&directionalLights[0]->data, sizeof(Components::DirectionalLight::Data));
		auto camcomp = camera->Get<Components::Camera>();
		auto camtrans = camera->Get<Components::Transform3D>();
		cameraTransform = camcomp->CameraMatrix;
        camPos = camtrans->GenRotTransMatrix();
        camPos(0, 3) *= -1;
        camPos(1, 3) *= -1;
        camPos(2, 3) *= -1;
		_materials = render->CreateConstantBuffer(sizeof(Components::Material::Data));
		//render->pCtx->PSSetConstantBuffers(0, 1, &_lights.p);
		initPointLights();
		initDirLights();
	}
	void ModelRenderer::initPointLights() {
		auto lights = parent->SelectEntities({ typeid(Components::PointLight), typeid(Components::Transform3D) });
		if (lights.empty()) {
			return;
		}
        
		std::vector<LibCommon::point_light> lightStructs = LibCommon::fuse_point_lights(lights);

        CComPtr<ID3D11Buffer> lightBuffer = createStructuredBuffer(render->pDev, &lightStructs[0], sizeof(LibCommon::point_light), lightStructs.size());
		_pointLights.Release();
		_pointLights = createStructuredBufferView(render->pDev, lightBuffer, 
			static_cast<UINT>(lightStructs.size()));
		
	}
	void ModelRenderer::initDirLights() {
		auto lights = parent->SelectEntities({ typeid(Components::DirectionalLight) });
		if (lights.empty()) {
			return;
		}
		auto lightStructs = LibCommon::fuse_dir_lights(lights);
        Eigen::Matrix4f viewtrans = camPos;
        viewtrans.col(3) = Eigen::Vector4f{ 0, 0, 0, 1 };
        for (auto& elm : lightStructs) {
            elm.direction = viewtrans * elm.direction;
            elm.direction.normalize();
        }
		_dirLights.Release();
		_dirLights = createStructuredBufferView(render->pDev, &lightStructs[0], sizeof(LibCommon::directional_light), lightStructs.size());
		render->pCtx->PSSetShaderResources(2, 1, &_dirLights.p);
	}
	void ModelRenderer::Process(LibCommon::Entity* e) {
		using namespace Components;
		auto model = e->Get<Model>();
		auto effect = e->Get<Effect>();
		
		auto transform = e->Get<Transform3D>();
		auto texture = e->GetOptional<Texture>();
		CComPtr<ID3D11DeviceContext> pCtx = render->pCtx;
		CComPtr<ID3D11Device> pDev = render->pDev;
		auto ps = Effects::GetHLSLPixelShader(pDev, effect->ps.name);
		auto vs = Effects::GetHLSLVertexShader(pDev, effect->vs.name, effect->vs.inputDesc);
		if (texture) {
			Direct3DTexture* tex = nullptr;
			if (texCache.count(e) > 0) {
				tex = &texCache.at(e);
			} else {
				tex = &texCache.emplace(e, *texture).first->second;
			}
			auto srv = tex->SRV(pDev);
			auto samp = tex->SamplerState(pDev);
			pCtx->PSSetShaderResources(0, 1, &srv);
			pCtx->PSSetSamplers(0, 1, &samp);

		}
		if (entityCache.count(e) == 0) {
			entityCache[e].indexBuffer = render->CreateIndexBuffer(*model);
			entityCache[e].vertexBuffer = render->CreateVertexBuffer(*model);
		}
		auto vertexBuffer = entityCache[e].vertexBuffer;
		auto indexBuffer = entityCache[e].indexBuffer;
		auto& material = e->Get<Components::Material>()->data;
		updateBuffer(render->pCtx, _materials, &material, sizeof(Components::Material::Data));
		LibCommon::Transforms trans;
        trans.model = transform->GenMatrix();
		trans.view = camPos;
		trans.proj = cameraTransform;
		auto transformBuffer = render->GetTransforms(trans);
		pCtx->IASetInputLayout(vs->getInputLayout(pDev));
		pCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		unsigned int stride = sizeof(LibCommon::Vertex);
		unsigned int offset = 0;
		pCtx->PSSetShaderResources(1, 1, &_pointLights.p);
		pCtx->IASetVertexBuffers(0, 1, &vertexBuffer.p, &stride, &offset);
		pCtx->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		pCtx->VSSetShader(vs->getShader(pDev), nullptr, 0);
		pCtx->PSSetShader(ps->getShader(pDev), nullptr, 0);
		pCtx->VSSetConstantBuffers(0, 1, &transformBuffer.p);
		pCtx->PSSetConstantBuffers(0, 1, &_materials.p);
		pCtx->DrawIndexed(static_cast<UINT>(model->indices.size()), 0, 0);
		
	}
	void ModelRenderer::OnEntityRemove(LibCommon::Entity* e) {
		if (entityCache.count(e) > 0) {
			entityCache.erase(e);
		}
		if (texCache.count(e) > 0) {
			texCache.erase(e);
		}
	}
}