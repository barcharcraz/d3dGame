#include "stdafx.h"
#include "Triangle.h"
#include <math.h>
#include <DirectXMath.h>

namespace LibDirect3D {
	Triangle::Triangle() {
		verts[0].Pos = Eigen::Vector3f(0.0f, 1.0f, 0.0f);
		verts[1].Pos = Eigen::Vector3f(-1.0f, -1.0f, 0.0f);
		verts[2].Pos = Eigen::Vector3f(1.0f, -1.0f, 0.0f);
		indices[0] = 2;
		indices[1] = 1;
		indices[2] = 0;
		receive.connect<Direct3DRenderingMessage*>([this](Direct3DRenderingMessage * msg){this->handleDraw(msg); });
	}
	void Triangle::initVertexBuffer(ID3D11Device1 * dev) {
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(VertexData) * 3; //we have three points in the triangle
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = verts;
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		HRESULT hr = dev -> CreateBuffer(&bufferDesc, &initData, &_pVertexBuffer);
		if(FAILED(hr)) {
			throw hr;
		}
	}
	void Triangle::initIndexBuffer(ID3D11Device1 * dev) {
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(unsigned int) * 3; //we have 3 indices
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem  = indices;
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		HRESULT hr = dev->CreateBuffer(&bufferDesc, &initData, &_pIndexBuffer);
		if(FAILED(hr)) {
			throw hr;
		}

	}
	void Triangle::handleDraw(Direct3DRenderingMessage * msg) {
		if(_pVertexBuffer == nullptr) {
			initVertexBuffer(msg->pDevice);
		}
		if(_pIndexBuffer == nullptr) {
			initIndexBuffer(msg->pDevice);
		}
		_pActiveShaders = msg->pShaders->getDefaultSet();
		
		msg->pContext->IASetInputLayout(_pActiveShaders.layout);
		msg->pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		unsigned int stride = sizeof(VertexData);
		unsigned int offset = 0;
		msg->pContext->IASetVertexBuffers(0, 1, &_pVertexBuffer.p, &stride, &offset);
		msg->pContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		msg->pContext->VSSetShader(_pActiveShaders.pVS, nullptr, 0);
		msg->pContext->PSSetShader(_pActiveShaders.pPS, nullptr, 0);
		msg->pContext->DrawIndexed(3, 0, 0);
	}
}