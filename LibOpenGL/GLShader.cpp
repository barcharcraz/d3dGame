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
        if(status == gl::FALSE_) {
            GLint infoLogLen;
            gl::GetShaderiv(shader, gl::INFO_LOG_LENGTH, &infoLogLen);
            errMsg.reserve(infoLogLen);
            GLchar *infoRaw = new GLchar[infoLogLen + 1];
            gl::GetShaderInfoLog(shader, infoLogLen, nullptr, infoRaw);
            errMsg.assign(infoRaw);
            delete[] infoRaw;
            return errMsg;
        }
        return "";
    }
}

namespace LibOpenGL {
    GLShader::GLShader ( GLenum type, const std::string& filename )
        : _type(type) {
            _shader = gl::CreateShader(_type);
            auto data = utils::slurpByLines(filename);
            shader_src = utils::SourceFile(std::move(data)); 
            
    }
    void GLShader::SetDefine(std::string define, std::string value) {
        shader_src.add_define(std::move(define), std::move(value));
    }
	void GLShader::SetDefine(std::string define, int value) {
		SetDefine(std::move(define), std::to_string(value));
	}
    void GLShader::SetDefine(std::string define) {
        shader_src.add_define(std::move(define));
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
        auto cdata = shader_src.cdata();
        gl::ShaderSource(_shader, cdata.size(), &cdata[0], nullptr);
        gl::CompileShader(_shader);
        auto error = get_compile_errors(_shader);
        if(error != "") {
            throw utils::graphics_api_error(error);
        }
    }

    

}
