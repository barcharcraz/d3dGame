#include "GLShader.h"
#include <Utils/files.h>
namespace {
	std::string get_compile_errors(GLuint shader) {
		std::string errMsg;
		GLuint status;
		gl::GetShaderiv(shader, gl::COMPILE_STATUS, &status);
		if(status == gl::FALSE_) {
			GLint infoLogLen;
			gl::GetShaderiv(shader, gl::INFO_LOG_LENGTH, &infoLogLen);
			errMsg->reserve(infoLogLen);
			gl::GetShaderInfoLog(shader, infoLogLen, nullptr, &errMsg);
			return errMsg;
		}
		return "";
	}
}

namespace LibOpenGL {
	GLShader::GLShader ( GLenum type, const std::string& filename )
		: _type(type) {
			_shader = gl::CreateShader(_type);
			std::string data = utils::slurpText(filename);
			gl::ShaderSource(_shader, 1, &data.c_str(), nullptr);
			gl::CompileShader(_shader);
			auto error = get_compile_errors(_shader);
			if(error != "") {
				
			}
			
	}

}