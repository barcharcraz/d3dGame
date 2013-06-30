#include "stdafx.h"
#include "Shaders.h"

namespace LibDirect3D {
	void Shaders::addPS(std::wstring name, CComPtr<ID3D11PixelShader> shader, CComPtr<ID3D11InputLayout> layout) {
		PSmap[name] = shader;
		ILmap[name] = layout;
	}
	void Shaders::addVS(std::wstring name, CComPtr<ID3D11VertexShader> shader, CComPtr<ID3D11InputLayout> layout) {
		VSmap[name] = shader;
		ILmap[name] = layout;
	}

	void Shaders::addPS( ID3D11Device * pDev, std::wstring name, const BYTE shaderBlob [], std::vector<D3D11_INPUT_ELEMENT_DESC> desc) {
		CComPtr<ID3D11VertexShader> pVS;
		pDev->CreateVertexShader(shaderBlob, sizeof(shaderBlob), nullptr, &pVS);
		PSmap[name] = pVS;
		CComPtr<ID3D11InputLayout> pIL;
		pDev->CreateInputLayout(desc.data, desc.size(), shaderBlob, sizeof(shaderBlob), &pIL);
		ILmap[name] = pIL;
		
	}
}