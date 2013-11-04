#include "stdafx.h"
#include <string>
#ifndef LIBOPENGL_GLPROGRAM_H
#define LIBOPENGL_GLPROGRAM_H
namespace Effects {
	class Effect; 
}
namespace LibOpenGL {
	class GLProgram {
	public:
		GLProgram(GLuint vertex, GLuint fragment);
		GLProgram(GLuint vertex, GLuint geom, GLuint fragment);
		explicit GLProgram(const Effects::Effect& effect);
		GLProgram(GLProgram&& other);
		GLProgram(const GLProgram& other) = delete;
		GLuint ProgramID();
		GLuint GetUniformLocation(const std::string& name);
		~GLProgram();
	private:
		GLuint _program;
	};
}

#endif