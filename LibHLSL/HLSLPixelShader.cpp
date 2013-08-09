#include "stdafx.h"
#include "HLSLPixelShader.h"
#include <d3dcompiler.h>
#include <Utils/files.h>
#include <Utils/strings.h>
namespace Effects {
	HLSLPixelShader::HLSLPixelShader(const std::string& filename) : _filename(filename) {

	}
	CComPtr<ID3D11PixelShader> HLSLPixelShader::getShader(CComPtr<ID3D11Device> pDev) {
		if (!_pShader) {
			auto ext = utils::getFileExtension(_filename);
			if (ext == "cso") {
				_pShader = loadCompiledFile(pDev);
			} else if (ext == "hlsl" || ext == "ps") {
				_pShader = loadTextFile(pDev);
			}
		}
		return _pShader;
	}
	//---------PRIVATE----------------
	CComPtr<ID3D11PixelShader> HLSLPixelShader::loadCompiledFile(CComPtr<ID3D11Device> pDev) {
		auto content = utils::slurpBinary(_filename);
		CComPtr<ID3D11PixelShader> ps;
		HRESULT hr;
		hr = pDev->CreatePixelShader(content.data(), static_cast<unsigned int>(content.size()), nullptr, &ps);
		if (FAILED(hr)) {
			throw hr;
		}
		return ps;
	}
	CComPtr<ID3D11PixelShader> HLSLPixelShader::loadTextFile(CComPtr<ID3D11Device> pDev) {
		CComPtr<ID3DBlob> shaderCode;
		HRESULT hr = S_OK;
		hr = D3DCompileFromFile(utils::widen(_filename).c_str(), nullptr, nullptr, "main", "ps_5_0", D3DCOMPILE_DEBUG, 0, &shaderCode, nullptr);
		if (FAILED(hr)) {
			throw hr;
		}
		CComPtr<ID3D11PixelShader> ps;
		hr = pDev->CreatePixelShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), nullptr, &ps);
		if (FAILED(hr)) {
			throw hr;
		}
		return ps;
	}
}