#include "GLShader.h"
#include <Utils/files.h>
#include <Utils/exceptions.h>
#include <Utils/preprocess.h>
#include <Utils/strings.h>
#include <iostream>
namespace {
    std::string get_compile_errors(GLuint shader) {
        std::string errMsg;
        GLint status;
        gl::GetShaderiv(shader, gl::COMPILE_STATUS, &status);
        if (status != gl::NO_ERROR_) {
            GLint infoLogLen;
            gl::GetShaderiv(shader, gl::INFO_LOG_LENGTH, &infoLogLen);
            errMsg.reserve(infoLogLen);
            GLchar *infoRaw = new GLchar[infoLogLen + 1];
            gl::GetShaderInfoLog(shader, infoLogLen, nullptr, infoRaw);
            errMsg.assign(infoRaw);
            delete [] infoRaw;
        }
        return errMsg;
    }
	bool get_is_compiled(GLuint shader) {
		int rv = 0;
		gl::GetShaderiv(shader, gl::COMPILE_STATUS, &rv);
		return rv != 0; //convert the int to a bool
	}
}

namespace LibOpenGL {
    GLShader::GLShader ( GLenum type, const std::string& filename )
        : _type(type) {
            _shader = gl::CreateShader(_type);
            shader_src = utils::load_source_file(filename);
            
    }
    void GLShader::SetDefine(std::string define, std::string value) {
        utils::add_define(&shader_src, std::move(define), std::move(value), 1);
    }
	void GLShader::SetDefine(std::string define, int value) {
		SetDefine(std::move(define), std::to_string(value));
	}
    void GLShader::SetDefine(std::string define) {
        utils::add_define(&shader_src, std::move(define), 1);
    }
    GLuint GLShader::ShaderID() {
        return _shader;
    }
    GLenum GLShader::ShaderType() {
        return _type;
    }


    GLShader::~GLShader() {
        gl::DeleteShader(_shader);
    }

    void GLShader::Compile() {
        const char* cdata = shader_src.c_str();
        gl::ShaderSource(_shader, 1, &cdata, nullptr);
        gl::CompileShader(_shader);
		auto error = get_compile_errors(_shader);
		if (error != "") {
			std::cerr << error << std::endl;
            std::cerr << "Source was: \n" << std::endl;
            std::cerr << cdata;
		}
		if (get_is_compiled(_shader) == false) {
			throw utils::graphics_api_error(error);
		}
    }

    

}
