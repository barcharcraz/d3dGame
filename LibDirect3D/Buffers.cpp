#include "stdafx.h"
#include "Buffers.h"
#include <cassert>
namespace LibDirect3D {
	CComPtr<ID3D11Buffer> createVertexBuffer(ID3D11Device* pDev, const std::vector<VertexData>& verts) {
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

	CComPtr<ID3D11Buffer> createIndexBuffer(ID3D11Device* pDev, const std::vector<unsigned int>& indices) {
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

	CComPtr<ID3D11Buffer> createConstantBuffer(ID3D11Device* pDev, const VSConstantBuffer& data) {
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

	//structured buffers
	CComPtr<ID3D11Buffer> createStructuredBuffer(ID3D11Device* pDev, const void* data, size_t structSize, size_t numElm) {
		HRESULT hr = S_OK;

		D3D11_BUFFER_DESC desc;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = static_cast<UINT>(structSize * numElm);
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = static_cast<UINT>(structSize);

		D3D11_SUBRESOURCE_DATA dat;
		dat.pSysMem = data;
		dat.SysMemPitch = 0;
		dat.SysMemSlicePitch = 0;
		CComPtr<ID3D11Buffer> retval;
		hr = pDev->CreateBuffer(&desc, &dat, &retval);
		if (FAILED(hr)) {
			throw std::system_error(hr, std::system_category());
		}
		return retval;
	}
	CComPtr<ID3D11Buffer> CreateStructuredBuffer(ID3D11Device* pDev, size_t structSize, size_t length) {
		HRESULT hr = S_OK;
		D3D11_BUFFER_DESC desc;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = static_cast<UINT>(structSize * length);
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = static_cast<UINT>(structSize);
		CComPtr<ID3D11Buffer> retval;
		hr = pDev->CreateBuffer(&desc, nullptr, &retval);
		if (FAILED(hr)) {
			throw std::system_error(hr, std::system_category());
		}
		return retval;
	}
	void updateConstantBuffer(ID3D11DeviceContext* pCtx, ID3D11Buffer* buffer, const void* data, size_t size) {
		HRESULT hr = S_OK;
		D3D11_MAPPED_SUBRESOURCE map;
		map.pData = 0;
		map.DepthPitch = 0;
		map.RowPitch = 0;
		//do a bounds check on the buffer if we are in debug mode
		assert(getBufferSize(buffer) >= size);
		hr = pCtx->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
		if (FAILED(hr)) {
			throw std::system_error(hr, std::system_category());
		}
		memcpy(map.pData, data, size);
		pCtx->Unmap(buffer, 0);
	}
	size_t getBufferSize(ID3D11Buffer* buffer) {
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		buffer->GetDesc(&desc);
		return desc.ByteWidth;
	}
}