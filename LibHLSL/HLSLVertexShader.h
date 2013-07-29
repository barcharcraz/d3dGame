#pragma once
#include <string>
#include <d3d11_2.h>
#include <atlbase.h>
#include <vector>
#include <Utils/strings.h>
#include <Utils/files.h>
namespace LibShaders {
	class HLSLVertexShader {
	public:
		HLSLVertexShader(const std::string& filename, const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputDesc);
		CComPtr<ID3D11VertexShader> getShader(ID3D11Device * pDev);
		CComPtr<ID3D11InputLayout> getInputLayout(ID3D11Device * pDev);
		
	private:
		CComPtr<ID3D11VertexShader> loadCompiledFile(ID3D11Device* pDev);
		CComPtr<ID3D11VertexShader> loadTextFile(ID3D11Device* pDev);
		std::string _filename;
		std::vector<D3D11_INPUT_ELEMENT_DESC> _desc;
		CComPtr<ID3D11VertexShader> _pShader;
		CComPtr<ID3D11InputLayout> _pLayout;
	};
}