#include "stdafx.h"
#include "Shaders.h"
#include <assert.h>
#include <Utils\files.h>

namespace LibDirect3D {
	Shaders::Shaders() {
		firstIL = ILmap.end();
		firstPS = PSmap.end();
		firstVS = VSmap.end();
	}
	void Shaders::addPS(const std::string& name, CComPtr<ID3D11PixelShader> shader, CComPtr<ID3D11InputLayout> layout) {
		PSmap[name] = shader;
		ILmap[name] = layout;
		if (firstPS == PSmap.end()) {
			firstPS = PSmap.find(name);
		}
		if (firstIL == ILmap.end()) {
			firstIL = ILmap.find(name);
		}
	}
	void Shaders::addVS(const std::string& name, CComPtr<ID3D11VertexShader> shader, CComPtr<ID3D11InputLayout> layout) {
		VSmap[name] = shader;
		ILmap[name] = layout;
		if (firstVS == VSmap.end()) {
			firstVS = VSmap.find(name);
		}
		if (firstIL == ILmap.end()) {
			firstIL = ILmap.find(name);
		}
	}

	void Shaders::addPS( ID3D11Device * pDev, const std::string& name, const BYTE shaderBlob [], size_t shaderSize, const std::vector<D3D11_INPUT_ELEMENT_DESC> &desc) {
		HRESULT hr;
		CComPtr<ID3D11PixelShader> pPS;
		hr = pDev->CreatePixelShader(shaderBlob, shaderSize, nullptr, &pPS);
		if (FAILED(hr)) {
			throw hr;
		}
		
		//PSmap.insert(std::pair<std::string, CComPtr<ID3D11PixelShader>>(name, pPS));
		CComPtr<ID3D11InputLayout> pIL;
		hr = pDev->CreateInputLayout(desc.data(), static_cast<unsigned int>(desc.size()), shaderBlob, shaderSize, &pIL);
		if (FAILED(hr)) {
			throw hr;
		}
		addPS(name, pPS, pIL);
		
		
	}
	void Shaders::addVS(ID3D11Device * pDev, const std::string& name, const BYTE shaderBlob [], size_t shaderSize, const std::vector<D3D11_INPUT_ELEMENT_DESC> &desc) {
		HRESULT hr;
		CComPtr<ID3D11VertexShader> pVS;
		hr = pDev->CreateVertexShader(shaderBlob, shaderSize, nullptr, &pVS);
		if (FAILED(hr)) {
			throw hr;
		}

		CComPtr<ID3D11InputLayout> pIL;
		hr = pDev->CreateInputLayout(desc.data(), static_cast<unsigned int>(desc.size()), shaderBlob, shaderSize, &pIL);
		if (FAILED(hr)) {
			throw hr;
		}
		addVS(name, pVS, pIL);
	}

	void Shaders::addPS(ID3D11Device * pDev, const std::string& filename, const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc) {
		auto buffer = utils::slurpBinary(filename);
		addPS(pDev, filename, buffer->data(),buffer->size(), desc);
	}
	void Shaders::addVS(ID3D11Device * pDev, const std::string& filename, const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc) {
		auto buffer = utils::slurpBinary(filename);
		addVS(pDev, filename, buffer->data(), buffer->size(), desc);
	}
	shaderSet Shaders::getSetWith(const std::string& vs, const std::string& ps) {
		shaderSet rv;
		//we want to use the input layout of the vertex shader object
		//if this does not match the layout of the other shaders than too bad
		rv.layout = ILmap.at(vs); 
		rv.pVS = VSmap.at(vs).p;
		rv.pPS = PSmap.at(ps).p;
		return rv;
	}
	
	bool Shaders::defaultSetExists() {
		if (firstPS == PSmap.end() ||
			firstVS == VSmap.end() ||
			firstIL == ILmap.end()) {
				return false;
		}
		else {
			return true;
		}
	}
	shaderSet Shaders::getDefaultSet() {
		if (!defaultSetExists()) {
			throw std::exception("no default shader defined");
		}
		shaderSet rv;
		rv.layout = firstIL->second;
		rv.pPS = firstPS->second;
		rv.pVS = firstVS->second;
		return rv;

	}
	shaderSet Shaders::getNamedSet(const std::string& name) {
		return namedSets.at(name);
	}

	bool Shaders::createNamedSet(const std::string& name, const std::string& vs, const std::string& ps) {
		if (namedSets.count(name)) {
			return false;
		}

		//start modifing internal state
		shaderSet newSet(getSetWith(vs, ps));

		//-----after this line no exceptions will be thrown
		//is there a copy here? I have no idea, I hope not
		namedSets[name] = newSet;
		assert(namedSets.count(name));

		return true;
	}
}