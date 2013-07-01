#pragma once
#include "stdafx.h"
#include <LibCommon\errors.h>

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
		void addPS(const std::string& name, CComPtr<ID3D11PixelShader> shader, CComPtr<ID3D11InputLayout> layout);
		void addVS(const std::string& name, CComPtr<ID3D11VertexShader> shader, CComPtr<ID3D11InputLayout> layout);


		//!\brief this function adds a pixel shader to the shaders collection
		//!			using the passed in compiled shader blob. Note that you
		//!			must pass in a vector of D3D11_INPUT_ELEMENT_DESCs that describe
		//!			not only the shader you are adding but also the other shaders you may
		//!			want to use with it. LibDirect3D does not yet implement the Function Linking
		//!			graph, when it does you will be able to piece together shaders
		//!			with much more granularity
		void addPS(ID3D11Device * pDev, const std::string& name, const BYTE shaderBlob [], std::vector<D3D11_INPUT_ELEMENT_DESC> desc);

		//!\brief this function adds a vertex shader to the shaders collection.
		//!			as with addPS this function takes a shader blob and a vector
		//!			of ID3D11_INPUT_ELEMENT_DESCs
		void addVS(ID3D11Device * pDev, const std::string& name, const BYTE shaderBlob [], std::vector<D3D11_INPUT_ELEMENT_DESC> desc);


		shaderSet getSetWith(const std::string& vs, const std::string& ps);
		shaderSet getNamedSet(const std::string& name);
		bool createNamedSet(const std::string& name, const std::string& vs, const std::string& ps);
	private:
		std::map<std::string, std::unique_ptr<shaderSet> > namedSets;
		std::map<std::string, CComPtr<ID3D11PixelShader> > PSmap;
		std::map<std::string, CComPtr<ID3D11VertexShader> > VSmap;
		std::map<std::string, CComPtr<ID3D11InputLayout> > ILmap;
	};
}