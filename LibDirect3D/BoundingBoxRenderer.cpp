#include "stdafx.h"
#include "BoundingBoxRenderer.h"
#include <LibComponents/AxisAlignedBB.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <stdexcept>
#include <LibEffects/EffectsManagement.h>
#include <LibEffects/Shader.h>
#include <LibCommon/Scene.h>
#include <LibComponents/Camera.h>
#include <LibComponents/Transform.h>
#include <LibHLSL/HLSLPixelShader.h>
#include <LibHLSL/HLSLVertexShader.h>
#include <LibHLSL/HLSLCache.h>
namespace LibDirect3D {
	namespace {
		struct SimpleMesh {
			std::vector<Eigen::Vector4f> position;
			std::vector<int> indices;
		};
		std::vector<Eigen::Vector4f> genModel(const Eigen::AlignedBox3f& aabb) {
			std::vector<Eigen::Vector4f> rv;
			for (unsigned int i = 0; i < 8; ++i) {
				auto corner = aabb.corner(static_cast<Eigen::AlignedBox3f::CornerType>(i));
				rv.push_back(Eigen::Vector4f{ corner.x(), corner.y(), corner.z(), 1 });
			}
			return rv;
		}
		std::vector<unsigned int> bbox_index = {
			0,2,2,3,3,1,1,0,
			0,4,4,6,6,2,2,0,
			2,6,6,7,7,3,3,2,
			3,7,7,5,5,1,1,3,
			0,1,1,5,5,4,4,0,
			4,6,6,7,7,5
		};
	}
	BoundingBoxRenderer::BoundingBoxRenderer(Direct3DRenderer* renderer)
		: System({ typeid(Components::AxisAlignedBB) }), render(renderer)
	{

	}
	void BoundingBoxRenderer::Init() {
		HRESULT hr = S_OK;
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = static_cast<UINT>(sizeof(Eigen::Vector4f) * 8);
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		hr = render->pDev->CreateBuffer(&desc, nullptr, &buffers.vertexBuffer);
		if (FAILED(hr)) {
			throw std::system_error(hr, std::system_category());
		}
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = static_cast<UINT>(sizeof(unsigned int) * bbox_index.size());
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA indexData;
		indexData.pSysMem = bbox_index.data();
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;
		hr = render->pDev->CreateBuffer(&desc, &indexData, &buffers.indexBuffer);
		if (FAILED(hr)) {
			throw std::system_error(hr, std::system_category());
		}

	}
	void BoundingBoxRenderer::PreProcess() {
		using namespace Eigen;
		auto camera = parent->SelectEntity({ typeid(Components::Camera) });
		auto camTrans = camera->Get<Components::Transform3D>();
		trans.model = Eigen::Affine3f::Identity().matrix();
		trans.view = (Translation3f(camTrans->position) * camTrans->rotation).matrix();
		trans.proj = camera->Get<Components::Camera>()->CameraMatrix.matrix();
	}
	void BoundingBoxRenderer::Process(LibCommon::Entity* ent) {
		HRESULT hr = S_OK;
		auto shader = Effects::ChooseEffect({ Effects::ShaderCaps::DEBUG_SOLID });
		auto verts = genModel(ent->Get<Components::AxisAlignedBB>()->CurAABB);
		D3D11_MAPPED_SUBRESOURCE sub;
		ZeroMemory(&sub, sizeof(sub));
		hr = render->pCtx->Map(buffers.vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		if (FAILED(hr)) {
			throw std::system_error(hr, std::system_category());
		}
		memcpy(sub.pData, verts.data(), sizeof(Eigen::Vector4f) * verts.size());
		render->pCtx->Unmap(buffers.vertexBuffer, 0);
		auto transformBuffer = render->GetTransforms(trans);
		auto ps = Effects::GetHLSLPixelShader(render->pDev, shader.ps.name);
		auto vs = Effects::GetHLSLVertexShader(render->pDev, shader.vs.name, shader.vs.inputDesc);
		render->pCtx->IASetInputLayout(vs->getInputLayout(render->pDev.p));
		render->pCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		unsigned int stride = sizeof(Eigen::Vector4f);
		unsigned int offset = 0;
		render->pCtx->IASetVertexBuffers(0, 1, &buffers.vertexBuffer.p, &stride, &offset);
		render->pCtx->IASetIndexBuffer(buffers.indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		render->pCtx->VSSetShader(vs->getShader(render->pDev.p), nullptr, 0);
		render->pCtx->PSSetShader(ps->getShader(render->pDev.p), nullptr, 0);
		render->pCtx->PSSetConstantBuffers(0, 1, &transformBuffer.p);
		render->pCtx->DrawIndexed(static_cast<UINT>(bbox_index.size()), 0, 0);
	}
}