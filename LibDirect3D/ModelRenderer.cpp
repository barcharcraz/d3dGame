#include "stdafx.h"
#include "ModelRenderer.h"
#include "Direct3DTexture.h"
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
#include <cstddef>
namespace LibDirect3D {
	ModelRenderer::ModelRenderer(const Direct3DRenderer& renderer)
		: System({ typeid(Components::Model), typeid(Components::Transform3D), typeid(Components::Effect) }), 
		render(&renderer)
	{
		
	}
	void ModelRenderer::Init() {
		auto camera = parent->SelectEntity({ typeid(Components::Camera), typeid(Components::Transform3D) });
		directionalLights = parent->SelectComponents<Components::DirectionalLight>();
		auto first = *directionalLights[0];
		
		int off = (int)offsetof(Components::DirectionalLight, Color);
		_lights = render->CreateConstantBuffer(((char*)directionalLights[0])+off, sizeof(Components::DirectionalLight) - off);
		auto camcomp = camera->Get<Components::Camera>();
		auto camtrans = camera->Get<Components::Transform3D>();
		cameraTransform = camcomp->CameraMatrix;
		camPos = camtrans->transform.matrix();
	}
	void ModelRenderer::Process(LibCommon::Entity* e) {
		using namespace Components;
		auto model = e->Get<Model>();
		auto ps = e->Get<Components::Effect>()->ps.hps;
		auto vs = e->Get<Components::Effect>()->vs.hvs;
		auto transform = e->Get<Transform3D>();
		auto texture = e->GetOptional<Texture>();
		CComPtr<ID3D11DeviceContext> pCtx = render->pCtx;
		CComPtr<ID3D11Device> pDev = render->pDev;
		if (texture) {
			texture->D3DTex()->SetRenderState(pDev, pCtx);
		}
		if (entityCache.count(e) == 0) {
			entityCache[e].indexBuffer = render->CreateIndexBuffer(*model);
			entityCache[e].vertexBuffer = render->CreateVertexBuffer(*model);
		}
		auto vertexBuffer = entityCache[e].vertexBuffer;
		auto indexBuffer = entityCache[e].indexBuffer;
		LibCommon::Transforms trans;
		trans.model = transform->transform.matrix();
		trans.view = camPos;
		trans.proj = cameraTransform;
		auto transformBuffer = render->GetTransforms(trans);
		pCtx->IASetInputLayout(vs->getInputLayout(pDev));
		pCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		unsigned int stride = sizeof(LibCommon::Vertex);
		unsigned int offset = 0;
		pCtx->IASetVertexBuffers(0, 1, &vertexBuffer.p, &stride, &offset);
		pCtx->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		pCtx->VSSetShader(vs->getShader(pDev), nullptr, 0);
		pCtx->PSSetShader(ps->getShader(pDev), nullptr, 0);
		pCtx->VSSetConstantBuffers(0, 1, &transformBuffer.p);
		pCtx->PSSetConstantBuffers(0, 1, &_lights.p);
		pCtx->DrawIndexed(static_cast<UINT>(model->indices.size()), 0, 0);
		
	}
	void ModelRenderer::OnEntityRemove(LibCommon::Entity* e) {
		if (entityCache.count(e) > 0) {
			entityCache.erase(e);
		}
	}
}