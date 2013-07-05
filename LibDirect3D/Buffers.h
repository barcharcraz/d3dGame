#pragma once
#include "stdafx.h"
#include "DataFormats.h"
//! \brief handle buffer creation and mangement
//!	       if you really want nobody is stopping
//!        you from just using the COM API but
//!        I like to keep as far away from COM
//!        as I can

namespace LibDirect3D {
	CComPtr<ID3D11Buffer> createVertexBuffer(ID3D11Device * pDev, const std::vector<VertexData>& verts);
	CComPtr<ID3D11Buffer> createIndexBuffer(ID3D11Device * pDev, const std::vector<unsigned int>& indices);
	CComPtr<ID3D11Buffer> createConstantBuffer(ID3D11Device * pDev, const VSConstantBuffer& data);
}