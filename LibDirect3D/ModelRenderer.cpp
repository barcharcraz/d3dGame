#include "stdafx.h"
#include "ModelRenderer.h"
#include <LibCommon/Data.h>
namespace LibDirect3D {
	ModelRenderer::ModelRenderer(const LibCommon::Model& model)
		: _model(model) 
	{
		init();
	}
	void ModelRenderer::init() {
		receive.connect<Direct3DRenderingMessage*>([this](Direct3DRenderingMessage * msg) {this->handleDraw(msg); });
	}
	void ModelRenderer::initBuffers(ID3D11Device * pDev) {
		HRESULT hr = S_OK;

		CComPtr<ID3D11Buffer> vertexBuffer;
		CComPtr<ID3D11Buffer> indexBuffer;

		D3D11_BUFFER_DESC vertexDesc;
		vertexDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexDesc.ByteWidth = static_cast<UINT>(sizeof(LibCommon::Vertex) * _model.verts.size());
		vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexDesc.CPUAccessFlags = 0;
		vertexDesc.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA vertexData;
		vertexData.pSysMem = _model.verts.data();
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;
		hr = pDev->CreateBuffer(&vertexDesc, &vertexData, &vertexBuffer);
		if (FAILED(hr)) {
			throw hr;
		}

		D3D11_BUFFER_DESC indexDesc;
		indexDesc.Usage = D3D11_USAGE_DEFAULT;
		indexDesc.ByteWidth = static_cast<UINT>(sizeof(int) * _model.indices.size());
		indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexDesc.CPUAccessFlags = 0;
		indexDesc.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA indexData;
		vertexData.pSysMem = _model.indices.data();
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;
		hr = pDev->CreateBuffer(&indexDesc, &indexData, &indexBuffer);
		if (FAILED(hr)) {
			throw hr;
		}

		_pVertexBuffer = std::move(vertexBuffer);
		_pIndexBuffer = std::move(indexBuffer);
	}
	void ModelRenderer::handleDraw(Direct3DRenderingMessage * msg) {
		
	}
}