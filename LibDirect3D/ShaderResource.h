#pragma once
#include "stdafx.h"
namespace LibDirect3D {
	CComPtr<ID3D11ShaderResourceView> createStructuredBufferView(CComPtr<ID3D11Device> pDev, CComPtr<ID3D11Buffer> buffer, unsigned int numElm);
	
}