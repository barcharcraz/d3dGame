#include "GLUniforms.h"

namespace LibOpenGL {
	void BindTexture(GLuint program, const std::string& name,
		GLuint texture) 
	{
		gl::UseProgram(program);
		GLuint baseLoc = gl::GetUniformLocation(program, name.c_str());
		gl::Uniform1ui(baseLoc, 0);
		gl::ActiveTexture(gl::TEXTURE0);
		gl::BindTexture(gl::TEXTURE_2D, texture);
	}
}