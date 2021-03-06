#include "stdafx.h"
#include "HLSLVertexShader.h"
#include <d3dcompiler.h>
#include <cassert>
namespace Effects {
	HLSLVertexShader::HLSLVertexShader(const std::string& filename, const std::vector<Effects::ShaderDesc>& inputDesc)
		: _filename(utils::fixupExtensionOptional(filename, "cso"))
	{
		for (auto& desc : inputDesc) {
			D3D11_INPUT_ELEMENT_DESC curDesc;
			curDesc.AlignedByteOffset = desc.AlignedByteOffset;
			curDesc.Format = static_cast<DXGI_FORMAT>(desc.Format);
			curDesc.InputSlot = desc.InputSlot;
			curDesc.InputSlotClass = static_cast<D3D11_INPUT_CLASSIFICATION>(desc.InputSlotClass);
			curDesc.InstanceDataStepRate = desc.InstanceDataStepRate;
			curDesc.SemanticIndex = desc.Index;
			curDesc.SemanticName = desc.ElementName.c_str();
			_desc.push_back(std::move(curDesc));
		}
	}
	CComPtr<ID3D11VertexShader> HLSLVertexShader::getShader(CComPtr<ID3D11Device> pDev) {
		if (!_pShader) {
			auto ext = utils::getFileExtension(_filename);
			if (ext == "cso") {
				_pShader = loadCompiledFile(pDev);
			} else if (ext == "hlsl" || ext == "vs") {
				_pShader = loadTextFile(pDev);
			}
		}
		return _pShader;
	}
	CComPtr<ID3D11InputLayout> HLSLVertexShader::getInputLayout(CComPtr<ID3D11Device> pDev) {
		if (!_pLayout) {
			_pShader = getShader(pDev);
		}
		return _pLayout;
	}
	CComPtr<ID3D11VertexShader> HLSLVertexShader::loadCompiledFile(CComPtr<ID3D11Device> pDev) {
		auto content = utils::slurpBinary(_filename);
		CComPtr<ID3D11VertexShader> vs;
		HRESULT hr = S_OK;
		hr = pDev->CreateVertexShader(content.data(), static_cast<unsigned int>(content.size()), nullptr, &vs);
		if (FAILED(hr)) {
			throw hr;
		}
		CComPtr<ID3D11InputLayout> layout;
		hr = pDev->CreateInputLayout(_desc.data(), static_cast<unsigned int>(_desc.size()), content.data(), content.size(), &layout);
		if (FAILED(hr)) {
			throw hr;
		}
		_pLayout = std::move(layout);
		return vs;
	}
	CComPtr<ID3D11VertexShader> HLSLVertexShader::loadTextFile(CComPtr<ID3D11Device> pDev) {
		CComPtr<ID3DBlob> shaderCode;
		HRESULT hr = S_OK;
		hr = D3DCompileFromFile(utils::widen(_filename).c_str(), nullptr, nullptr, "main", "vs_5_0", D3DCOMPILE_DEBUG, 0, &shaderCode, nullptr);
		if (FAILED(hr)) {
			throw hr;
		}
		CComPtr<ID3D11VertexShader> vs;
		hr = pDev->CreateVertexShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), nullptr, &vs);
		if (FAILED(hr)) {
			throw hr;
		}
		CComPtr<ID3D11InputLayout> layout;
		hr = pDev->CreateInputLayout(_desc.data(), static_cast<unsigned int>(_desc.size()), shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), &layout);
		if (FAILED(hr)) {
			throw hr;
		}
		_pLayout = layout;
		return vs;
	}
}