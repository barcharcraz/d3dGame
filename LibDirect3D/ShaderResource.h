#pragma once
#include "stdafx.h"
namespace LibDirect3D {
	CComPtr<ID3D11ShaderResourceView> createStructuredBufferView(ID3D11Device* pDev, ID3D11Buffer* buffer, unsigned int numElm);
	//! \brief this function creates a structured buffer view directly from data
	//!
	//! internally it is createing a buffer and than using that buffer to create the SRV
	//! if you need to update stuff every draw or even every frame you should consider keeping
	//! the buffer around and using updateBuffer to map in new data
	CComPtr<ID3D11ShaderResourceView> createStructuredBufferView(ID3D11Device* pDev, const void* data, size_t size, size_t length);
	
}