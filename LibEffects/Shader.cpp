//warning, crossplatform mess follows
#include "stdafx.h"
#include <config.h>
#include <Utils/files.h>
#include <Utils/exceptions.h>
#include <map>

#include "Shader.h"
#ifdef USE_DIRECT3D
#include <LibHLSL/HLSLPixelShader.h>
#include <LibHLSL/HLSLVertexShader.h>
#endif
#ifdef USE_OPENGL
#include <LibGLSL/GLSLPixelShader.h>
#include <LibGLSL/GLSLVertexShader.h>
#endif
namespace Effects {
#ifdef USE_DIRECT3D
	static std::map<std::string, HLSLPixelShader> hps_map;
	static std::map<std::string, HLSLVertexShader> hvs_map;
#endif

	VertexShader::VertexShader(const std::string& filename, const std::vector<ShaderDesc>& desc)
		: name(filename) {
		auto ext = utils::getFileExtension(filename);
		if (ext == "") {
#ifdef USE_DIRECT3D
			if (utils::fileExists(filename + ".cso")) {
				Load(filename + ".cso", desc);
			}
#endif
		} else {
			Load(filename, desc);
		}
	}
	void VertexShader::Load(const std::string& filename, const std::vector<ShaderDesc>& desc) {
		auto ext = utils::getFileExtension(filename);
		if (ext == "cso") {
#ifdef USE_DIRECT3D
			if (hvs_map.count(filename) == 0) {
				auto& res = hvs_map.emplace(filename, HLSLVertexShader(filename, desc)).first->second;
				hvs = &res;
			} else {
				hvs = &hvs_map.at(filename);
			}
#else
			throw utils::not_supported_error("Tried to load an HLSL shader without HLSL support");
#endif
		}
	}
    
	//Pixel shader stuff
	PixelShader::PixelShader(const std::string& filename)
		: name(filename) {
		auto ext = utils::getFileExtension(filename);
		if (filename == "") {
#ifdef USE_DIRECT3D
			if (utils::fileExists(filename + ".cso")) {
				Load(filename + ".cso");
			}
#endif
		} else {
			Load(filename);
		}
	}
	void PixelShader::Load(const std::string& filename) {
		auto ext = utils::getFileExtension(filename);
		if (ext == "cso") {
#ifdef USE_DIRECT3D
			if(hps_map.count(filename) == 0) {
				auto& res = hps_map.emplace(filename, HLSLPixelShader(filename)).first->second;
				hps = &res;
			} else {
				hps = &hps_map.at(filename);
			}
#else
			throw utils::not_supported_error("Tried to load an HLSL shader without HLSL support");
#endif
		}
	}
}