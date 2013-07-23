#include "stdafx.h"
#include "Triangle.h"
#include "Buffers.h"
#include <math.h>
#include <DirectXMath.h>

namespace LibDirect3D {
	Triangle::Triangle() {

		verts.emplace_back(VertexData{ Eigen::Vector3f(0.0f, 0.5f, 0.0f) });
		verts.emplace_back(VertexData{ Eigen::Vector3f(-0.5f, -0.5f, 0.0f) });
		verts.emplace_back(VertexData{ Eigen::Vector3f(0.5f, -0.5f, 0.0f) });
		indices.push_back(2);
		indices.push_back(1);
		indices.push_back(0);
		camera = Eigen::Affine3f::Identity();
		camera *= Eigen::AngleAxisf(1.0f, Eigen::Vector3f::UnitY());
		
		messenger->connect(&Triangle::handleDraw, this);
	}
	void Triangle::handleDraw(Direct3DRenderingMessage * msg) {
		if(_pVertexBuffer == nullptr) {
			_pVertexBuffer = createVertexBuffer(msg->pDevice, verts);
		}
		if(_pIndexBuffer == nullptr) {
			_pIndexBuffer = createIndexBuffer(msg->pDevice, indices);
		}
		if (_pConstantBuffer == nullptr) {
			_pConstantBuffer = createConstantBuffer(msg->pDevice, VSConstantBuffer{ camera.matrix() });
		}
		_pActiveShaders = msg->pShaders->getDefaultSet();
		
		msg->pContext->IASetInputLayout(_pActiveShaders.layout);
		msg->pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		unsigned int stride = sizeof(VertexData);
		unsigned int offset = 0;
		msg->pContext->IASetVertexBuffers(0, 1, &_pVertexBuffer.p, &stride, &offset);
		msg->pContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		msg->pContext->VSSetShader(_pActiveShaders.pVS, nullptr, 0);
		msg->pContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer.p);
		msg->pContext->PSSetShader(_pActiveShaders.pPS, nullptr, 0);
		msg->pContext->DrawIndexed(3, 0, 0);
	}
}