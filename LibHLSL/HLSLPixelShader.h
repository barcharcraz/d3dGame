#pragma once
#include "stdafx.h"

namespace LibShaders {
	class HLSLPixelShader {
	public:
		HLSLPixelShader(const std::string& filename);
		CComPtr<ID3D11PixelShader> getShader(ID3D11Device* pDev);
	private:
		CComPtr<ID3D11PixelShader> loadCompiledFile(ID3D11Device * pDev);
		CComPtr<ID3D11PixelShader> loadTextFile(ID3D11Device * pDev);
		std::string _filename;
		CComPtr<ID3D11PixelShader> _pShader;
	};
}