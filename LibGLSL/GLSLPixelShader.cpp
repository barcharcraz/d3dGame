#include "GLSLPixelShader.h"
namespace Effects {
	GLSLPixelShader::GLSLPixelShader(const std::string &filename, const std::vector<ShaderDesc> &layout)
		: _filename(filename), _layout(layout)
	{

	}
	GLSLPixelShader::~GLSLPixelShader() {

	}
	//private functions
	void GLSLPixelShader::init() {
		_shader = glCreateDebugObjectMESA()
	}
}
