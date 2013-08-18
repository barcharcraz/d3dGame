#pragma once
#include "stdafx.h"
#include "DataFormats.h"
//! \brief handle buffer creation and mangement
//!	       if you really want nobody is stopping
//!        you from just using the COM API but
//!        I like to keep as far away from COM
//!        as I can

namespace LibDirect3D {
	CComPtr<ID3D11Buffer> createVertexBuffer(ID3D11Device* pDev, const std::vector<VertexData>& verts);
	CComPtr<ID3D11Buffer> createIndexBuffer(ID3D11Device* pDev, const std::vector<unsigned int>& indices);
	CComPtr<ID3D11Buffer> createConstantBuffer(ID3D11Device* pDev, const VSConstantBuffer& data);
	CComPtr<ID3D11Buffer> createStructuredBuffer(ID3D11Device* pDev, const void* data, size_t structSize, size_t length);
	CComPtr<ID3D11Buffer> createStructuredBuffer(ID3D11Device* pDev, size_t size, size_t length);
	void updateBuffer(ID3D11DeviceContext* pCtx, ID3D11Buffer* buffer, const void* data, size_t size);
	size_t getBufferSize(ID3D11Buffer* buffer);
}