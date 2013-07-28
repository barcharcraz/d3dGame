#include "stdafx.h"
#include "ModelRenderer.h"
#include <LibCommon/Data.h>
#include <LibComponents/Model.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Camera.h>
namespace LibDirect3D {
	ModelRenderer::ModelRenderer(const Direct3DRenderer& renderer)
		: System({ typeid(Components::Model), typeid(Components::Transform3D) }), pCtx(renderer.m_pContext), pDev(renderer.m_pDevice)
	{
		
	}
	void ModelRenderer::Init() {
		auto camera = parent->SelectEntity({ typeid(Components::Camera) });
		cameraTransform = &camera->Get<Components::Camera>()->CameraMatrix;
		createConstantBuffers();
	}
	void ModelRenderer::createConstantBuffers() {
		HRESULT hr = S_OK;
		CComPtr<ID3D11Buffer> transformBuffer;
		D3D11_BUFFER_DESC transDesc;
		transDesc.Usage = D3D11_USAGE_DYNAMIC;
		transDesc.ByteWidth = static_cast<UINT>(sizeof(LibCommon::Transforms));
		transDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		transDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		transDesc.MiscFlags = 0;
		transDesc.StructureByteStride = 0;

		hr = pDev->CreateBuffer(&transDesc, nullptr, &transformBuffer);
		if (FAILED(hr)) {
			throw hr;
		}
		_pTransformBuffer = std::move(transformBuffer);

	}
	CComPtr<ID3D11Buffer> ModelRenderer::createVertexBuffer(const Components::Model& model) {
		HRESULT hr = S_OK;
		CComPtr<ID3D11Buffer> vertexBuffer;
		D3D11_BUFFER_DESC vertexDesc;
		vertexDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexDesc.ByteWidth = static_cast<UINT>(sizeof(LibCommon::Vertex) * model.verts.size());
		vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexDesc.CPUAccessFlags = 0;
		vertexDesc.MiscFlags = 0;
		vertexDesc.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA vertexData;
		vertexData.pSysMem = model.verts.data();
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;
		hr = pDev->CreateBuffer(&vertexDesc, &vertexData, &vertexBuffer);
		if (FAILED(hr)) {
			throw hr;
		}
		return vertexBuffer;
	}
	CComPtr<ID3D11Buffer> ModelRenderer::createIndexBuffer(const Components::Model& model) {
		HRESULT hr = S_OK;
		CComPtr<ID3D11Buffer> indexBuffer;
		D3D11_BUFFER_DESC indexDesc;
		indexDesc.Usage = D3D11_USAGE_DEFAULT;
		indexDesc.ByteWidth = static_cast<UINT>(sizeof(int) * model.indices.size());
		indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexDesc.CPUAccessFlags = 0;
		indexDesc.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA indexData;
		indexData.pSysMem = model.indices.data();
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;
		hr = pDev->CreateBuffer(&indexDesc, &indexData, &indexBuffer);
		if (FAILED(hr)) {
			throw hr;
		}
		return indexBuffer;
	}
	void ModelRenderer::updateTransformBuffer(const Components::Transform3D& transform) {
		using namespace LibCommon;
		HRESULT hr = S_OK;
		
		auto worldViewTransform = (*cameraTransform) * transform.transform.matrix();
		constTransforms.worldView = worldViewTransform;
		D3D11_MAPPED_SUBRESOURCE map;
		map.pData = 0;
		map.DepthPitch = 0;
		map.RowPitch = 0;
		hr = pCtx->Map(_pTransformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
		if (FAILED(hr)) {
			throw hr;
		}
		memcpy(map.pData, &transform, sizeof(transform));
		pCtx->Unmap(_pTransformBuffer, 0);

	}
	void ModelRenderer::Process(LibCommon::Entity* e) {
		using namespace Components;
		auto model = e->Get<Model>();
		auto transform = e->Get<Transform3D>();
		CComPtr<ID3D11Buffer> indexBuffer = createIndexBuffer(*model);
		CComPtr<ID3D11Buffer> vertexBuffer = createVertexBuffer(*model);
		updateTransformBuffer(*transform);
		pCtx->IASetInputLayout
	}
	void ModelRenderer::handleDraw(Direct3DRenderingMessage * msg) {
		if (_pIndexBuffer == nullptr || _pVertexBuffer == nullptr || _pTransformBuffer == nullptr) {
			initConstantBuffers(msg->pDevice);
			initVertexBuffers(msg->pDevice);
			initIndexBuffer(msg->pDevice);
		}
		updateTransformBuffer(msg->pContext);
		_activeShaders = msg->pShaders->getDefaultSet();
		msg->pContext->IASetInputLayout(_activeShaders.layout);
		msg->pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		unsigned int stride = sizeof(LibCommon::Vertex);
		unsigned int offset = 0;
		msg->pContext->IASetVertexBuffers(0, 1, &_pVertexBuffer.p, &stride, &offset);
		msg->pContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		msg->pContext->PSSetShader(_activeShaders.pPS, nullptr, 0);
		msg->pContext->VSSetShader(_activeShaders.pVS, nullptr, 0);
		msg->pContext->VSSetConstantBuffers(0, 1, &_pTransformBuffer.p);
		msg->pContext->DrawIndexed(static_cast<UINT>(_model.indices.size()), 0, 0);
	}
}