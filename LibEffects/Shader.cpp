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

	VertexShader::VertexShader(const std::string& filename, const std::vector<ShaderDesc>& desc)
		: name(filename), inputDesc(desc) {
		//auto ext = utils::getFileExtension(filename);
	}
    
	//Pixel shader stuff
	PixelShader::PixelShader(const std::string& filename)
		: name(filename) {
		//auto ext = utils::getFileExtension(filename);
	}
}