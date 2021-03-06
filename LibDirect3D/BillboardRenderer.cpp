#include "stdafx.h"
#include "BillboardRenderer.h"
#include "Direct3DTexture.h"
#include <RenderingUtils/ModelProcessing.h>
#include <LibCommon/Scene.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Texture.h>
#include <LibComponents/Camera.h>
#include <LibComponents/Billboard.h>
#include <LibComponents/Effect.h>
#include <LibHLSL/HLSLCache.h>
namespace LibDirect3D {
	BillboardRenderer::BillboardRenderer(Direct3DRenderer* renderer)
		: System({typeid(Components::Billboard), typeid(Components::Transform3D), typeid(Components::Effect)}), 
		render(renderer)
	{

	}
	void BillboardRenderer::PreProcess() {
		using namespace Eigen;
		auto camera = parent->SelectEntity({ typeid(Components::Camera), typeid(Components::Transform3D) });
		auto viewTrans = camera->Get<Components::Transform3D>();
		view = (Translation3f(viewTrans->position) * viewTrans->rotation).matrix();
		proj = camera->Get<Components::Camera>()->CameraMatrix;
		view(0, 3) *= -1;
		view(1, 3) *= -1;
		view(2, 3) *= -1;

	}
	void BillboardRenderer::Process(LibCommon::Entity* ent) {
		using namespace Components;
		render->EnableAlphaBlending();
		auto model = ent->GetOptional<Model>();
		auto effect = ent->Get<Effect>();
		auto transform = ent->Get<Transform3D>();
		auto vs = Effects::GetHLSLVertexShader(render->pDev, effect->vs.name, effect->vs.inputDesc);
		auto ps = Effects::GetHLSLPixelShader(render->pDev, effect->ps.name);
		auto texture = ent->GetOptional<Texture>();
		if (texture) {
			Direct3DTexture* tex = nullptr;
			auto texIter = texCache.find(ent);
			if (texIter == texCache.end()) {
				tex = &texCache.emplace(ent, *texture).first->second;
			} else {
				tex = &texIter->second;
			}
			auto srv = tex->SRV(render->pDev);
			auto samp = tex->SamplerState(render->pDev);
			render->pCtx->PSSetShaderResources(0, 1, &srv);
			render->pCtx->PSSetSamplers(0, 1, &samp);
		}
		if (nullptr == model) {
			auto bboard = ent->Get<Billboard>();
			auto newModel = utils::generate_quad(bboard->width, bboard->height);
			ent->AddComponent<Model>(std::move(newModel));
			model = ent->Get<Model>();
		}
		auto iter = entCache.find(ent);
		if (iter == entCache.end()) {
			res newRes;
			newRes.indexBuf = render->CreateIndexBuffer(*model);
			newRes.vertexBuf = render->CreateVertexBuffer(*model);
			iter = entCache.emplace(ent, std::move(newRes)).first;
		}
		LibCommon::Transforms trans;
		Eigen::Matrix4f invView = view;
		invView.rightCols<1>() = Eigen::Vector4f{ 0, 0, 0, 1 };

		invView = invView.transpose().inverse().eval();
		trans.model = transform->GenMatrix() * invView.inverse();
		trans.view = view;
		trans.proj = proj;
		auto transformBuffer = render->GetTransforms(trans);
		
		render->pCtx->IASetInputLayout(vs->getInputLayout(render->pDev.p));
		render->pCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		unsigned int stride = sizeof(LibCommon::Vertex);
		unsigned int offset = 0;
		render->pCtx->IASetVertexBuffers(0, 1, &iter->second.vertexBuf.p, &stride, &offset);
		render->pCtx->IASetIndexBuffer(iter->second.indexBuf.p, DXGI_FORMAT_R32_UINT, 0);
		render->pCtx->VSSetShader(vs->getShader(render->pDev.p), nullptr, 0);
		render->pCtx->PSSetShader(ps->getShader(render->pDev.p), nullptr, 0);
		render->pCtx->VSSetConstantBuffers(0, 1, &transformBuffer.p);
		render->pCtx->DrawIndexed(static_cast<UINT>(model->indices.size()), 0, 0);
		render->DisableAlphaBlending();
	}
	void BillboardRenderer::OnEntityRemove(LibCommon::Entity* ent) {
		auto iter = entCache.find(ent);
		if (iter != entCache.end()) {
			entCache.erase(iter);
		}
		auto texIter = texCache.find(ent);
		if (texIter != texCache.end()) {
			texCache.erase(texIter);
		}
	}
}
