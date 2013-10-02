#include "GLProgram.h"
#include <Utils/exceptions.h>
#include <vector>
#include <string>
namespace {
	GLint checkLinkStatus(GLuint program, std::string* errMsg) {
		GLint rv;
		gl::GetProgramiv(program, gl::LINK_STATUS, &rv);
		if(rv == gl::FALSE_) {
			GLint errLen;
			gl::GetProgramiv(program, gl::INFO_LOG_LENGTH, &errLen);
			errMsg->reserve(errLen);
			GLchar* rawInfo = new GLchar[errLen + 1];
			gl::GetProgramInfoLog(program, errLen, nullptr, rawInfo);
			errMsg->assign(rawInfo);
			delete[] rawInfo;
			
		}
		return rv;
	}
	GLuint CreateProgram(const std::vector<GLuint>& shaders) {
		GLuint rv = gl::CreateProgram();
		for(auto shader : shaders) {
			gl::AttachShader(rv, shader);
		}
		gl::LinkProgram(rv);
		std::string errMsg = "";
		auto status = checkLinkStatus(rv, &errMsg);
		if(status == gl::FALSE_) {
			throw utils::graphics_api_error(errMsg);
		}
		for(auto shader : shaders) {
			gl::DetachShader(rv, shader);
		}
		
		return rv;
	}
}

namespace LibOpenGL {
	GLProgram::GLProgram ( GLuint vertex, GLuint fragment ) {
		_program = CreateProgram({vertex, fragment});
	}
	GLProgram::GLProgram ( GLuint vertex, GLuint geom, GLuint fragment ) {
		_program = CreateProgram({vertex, geom, fragment});
	}
	GLProgram::GLProgram ( LibOpenGL::GLProgram && other ) {
		_program = other._program;
		other._program = 0;
	}

	GLuint GLProgram::ProgramID() {
		return _program;
	}

	GLProgram::~GLProgram() {
		if(_program != 0) { 
			gl::DeleteProgram(_program);
		}
	}



}