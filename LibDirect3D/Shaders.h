#pragma once
#include "stdafx.h"

namespace LibDirect3D {
	struct shaderSet {
		ID3D11PixelShader * pPS;
		ID3D11VertexShader * pVS;
		ID3D11InputLayout * layout;
	};

	//! \brief a collection of various shaders
	//!			that associates sets of shaders
	//!			with relevant structures
	class Shaders {
	public:
		void addPS(std::wstring name, CComPtr<ID3D11PixelShader> shader, CComPtr<ID3D11InputLayout> layout);
		void addVS(std::wstring name, CComPtr<ID3D11VertexShader> shader, CComPtr<ID3D11InputLayout> layout);

		void addPS(ID3D11Device * pDev, std::wstring name, const BYTE shaderBlob [], std::vector<D3D11_INPUT_ELEMENT_DESC> desc);
		void addVS(ID3D11Device * pDev, std::wstring name, const BYTE shaderBlob [], std::vector<D3D11_INPUT_ELEMENT_DESC> desc);
	private:
		std::map<std::wstring, CComPtr<ID3D11PixelShader> > PSmap;
		std::map<std::wstring, CComPtr<ID3D11VertexShader> > VSmap;
		std::map<std::wstring, CComPtr<ID3D11InputLayout> > ILmap;
	};
}