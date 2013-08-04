#pragma once
#include "stdafx.h"

namespace LibShaders {
	class HLSLPixelShader {
	public:
		HLSLPixelShader(const std::string& filename);
		CComPtr<ID3D11PixelShader> getShader(CComPtr<ID3D11Device> pDev);
	private:
		CComPtr<ID3D11PixelShader> loadCompiledFile(CComPtr<ID3D11Device> pDev);
		CComPtr<ID3D11PixelShader> loadTextFile(CComPtr<ID3D11Device> pDev);
		std::string _filename;
		CComPtr<ID3D11PixelShader> _pShader;
	};
}