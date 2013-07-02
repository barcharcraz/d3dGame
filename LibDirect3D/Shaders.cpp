#include "stdafx.h"
#include "Shaders.h"
#include <assert.h>

namespace LibDirect3D {
	void Shaders::addPS(const std::string& name, CComPtr<ID3D11PixelShader> shader, CComPtr<ID3D11InputLayout> layout) {
		PSmap[name] = shader;
		ILmap[name] = layout;
	}
	void Shaders::addVS(const std::string& name, CComPtr<ID3D11VertexShader> shader, CComPtr<ID3D11InputLayout> layout) {
		VSmap[name] = shader;
		ILmap[name] = layout;
	}

	void Shaders::addPS( ID3D11Device * pDev, const std::string& name, const BYTE shaderBlob [], const std::vector<D3D11_INPUT_ELEMENT_DESC> &desc) {
		HRESULT hr;
		CComPtr<ID3D11PixelShader> pPS;
		hr = pDev->CreatePixelShader(shaderBlob, sizeof(shaderBlob), nullptr, &pPS);
		if (FAILED(hr)) {
			throw hr;
		}
		PSmap[name] = pPS;
		CComPtr<ID3D11InputLayout> pIL;
		hr = pDev->CreateInputLayout(desc.data(), static_cast<unsigned int>(desc.size()), shaderBlob, sizeof(shaderBlob), &pIL);
		if (FAILED(hr)) {
			throw hr;
		}
		ILmap[name] = pIL;
		
		
	}
	void Shaders::addVS(ID3D11Device * pDev, const std::string& name, const BYTE shaderBlob [], const std::vector<D3D11_INPUT_ELEMENT_DESC> &desc) {
		HRESULT hr;
		CComPtr<ID3D11VertexShader> pVS;
		hr = pDev->CreateVertexShader(shaderBlob, sizeof(shaderBlob), nullptr, &pVS);
		if (FAILED(hr)) {
			throw hr;
		}
		VSmap[name] = pVS;

		CComPtr<ID3D11InputLayout> pIL;
		hr = pDev->CreateInputLayout(desc.data(), static_cast<unsigned int>(desc.size()), shaderBlob, sizeof(shaderBlob), &pIL);
		if (FAILED(hr)) {
			throw hr;
		}
		ILmap[name] = pIL;
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
	shaderSet* Shaders::getDefaultSet() {
		if (defaultSetName == nullptr) {
			throw std::exception("no default shader defined");
		}
		return namedSets.at(*defaultSetName).get();
	}
	shaderSet* Shaders::getNamedSet(const std::string& name) {
		return namedSets.at(name).get();
	}

	bool Shaders::createNamedSet(const std::string& name, const std::string& vs, const std::string& ps) {
		if (namedSets.count(name)) {
			return false;
		}

		//start modifing internal state
		std::unique_ptr<shaderSet> newSet = std::make_unique<shaderSet>(getSetWith(vs, ps));
		//we successfully added the set to the list of sets, it is now
		//safe to set the default name, note that this CAN fail but if it does
		//we are still in a consistant state
		if (defaultSetName == nullptr) {
			defaultSetName = std::make_unique<std::string>(name);
		}
		//-----after this line no exceptions will be thrown
		//is there a copy here? I have no idea, I hope not
		namedSets[name] = std::move(newSet);
		assert(namedSets.count(name));

		return true;
	}
}