#include "stdafx.h"
#include "Buffers.h"
namespace LibDirect3D {
	CComPtr<ID3D11Buffer> createVertexBuffer(ID3D11Device * pDev, const std::vector<VertexData>& verts) {
		CComPtr<ID3D11Buffer> retval;
		D3D11_BUFFER_DESC desc;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = static_cast<UINT>(sizeof(VertexData) * verts.size());
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = verts.data();
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;
		
		HRESULT hr = pDev->CreateBuffer(&desc, &initData, &retval);
		if (FAILED(hr)) {
			throw hr;
		}
		return retval;
	}

	CComPtr<ID3D11Buffer> createIndexBuffer(ID3D11Device * pDev, const std::vector<unsigned int>& indices) {
		CComPtr<ID3D11Buffer> retval;

		D3D11_BUFFER_DESC desc;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = static_cast<UINT>(sizeof(unsigned int) * indices.size());
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = indices.data();
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;
		HRESULT hr = pDev->CreateBuffer(&desc, &initData, &retval);
		if (FAILED(hr)) {
			throw hr;
		}
		return retval;
	}

	CComPtr<ID3D11Buffer> createConstantBuffer(ID3D11Device * pDev, const VSConstantBuffer& data) {
		CComPtr<ID3D11Buffer> retval;
		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = sizeof(VSConstantBuffer);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &data;
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		HRESULT hr = pDev->CreateBuffer(&desc, &initData, &retval);
		if (FAILED(hr)) {
			throw hr;
		}
		return retval;
	}
}