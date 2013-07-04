#pragma once
#include "stdafx.h"
#include <fstream>
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
		Shaders();
		void addPS(const std::string& name, CComPtr<ID3D11PixelShader> shader, CComPtr<ID3D11InputLayout> layout);
		void addVS(const std::string& name, CComPtr<ID3D11VertexShader> shader, CComPtr<ID3D11InputLayout> layout);

		//!\brief this function adds a pixel shader to the shaders collection
		//!			using the passed in compiled shader blob. Note that you
		//!			must pass in a vector of D3D11_INPUT_ELEMENT_DESCs that describe
		//!			not only the shader you are adding but also the other shaders you may
		//!			want to use with it. LibDirect3D does not yet implement the Function Linking
		//!			graph, when it does you will be able to piece together shaders
		//!			with much more granularity
		void addPS(ID3D11Device * pDev, const std::string& name, const BYTE shaderBlob [], size_t shaderSize, const std::vector<D3D11_INPUT_ELEMENT_DESC> &desc);

		//!\brief this function adds a vertex shader to the shaders collection.
		//!			as with addPS this function takes a shader blob and a vector
		//!			of ID3D11_INPUT_ELEMENT_DESCs
		void addVS(ID3D11Device * pDev, const std::string& name, const BYTE shaderBlob [], size_t shaderSize, const std::vector<D3D11_INPUT_ELEMENT_DESC> &desc);

		//! \brief addes a shader from a compiled cso shader file
		//! \exception strong if this function throws the internal state of the object
		//!            will not change
		void addPS(ID3D11Device * pDev, const std::string& filename, const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc);
		//! \brief adds a shader from a compiled cso file
		//! \exception strong if this function throws the internal stat of the object
		//!            will not change
		void addVS(ID3D11Device * pDev, const std::string& filename, const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc);
		//! \brief gets the default shader set if one exists
		//!		   if one does not exist it throws and exception
		//! \exception strong
		//! \exception std::exception if no default shader exists
		shaderSet getDefaultSet();
		shaderSet getSetWith(const std::string& vs, const std::string& ps);
		shaderSet getNamedSet(const std::string& name);

		//! \brief This function creates a named shader set and stores that set
		//!        in an internal mpa
		//! \exception strong if this function throws an exception its internal state
		//!            will remain consistant
		bool createNamedSet(const std::string& name, const std::string& vs, const std::string& ps);
	private:
		//! \brief checks to see if we have one element in all of the maps, and
		//!        thus can return a default set
		//! \exception strong
		bool defaultSetExists();

		std::string defaultSetName;
		std::map<std::string, shaderSet > namedSets;
		typedef std::map<std::string, CComPtr<ID3D11PixelShader>> PSmap_t;
		typedef std::map<std::string, CComPtr<ID3D11VertexShader>> VSmap_t;
		typedef std::map<std::string, CComPtr<ID3D11InputLayout>> ILmap_t;
		PSmap_t PSmap;
		VSmap_t VSmap;
		ILmap_t ILmap;
		PSmap_t::iterator firstPS;
		VSmap_t::iterator firstVS;
		ILmap_t::iterator firstIL;
	};
}