#include "stdafx.h"

#ifndef LIBOPENGL_GLPROGRAM_H
#define LIBOPENGL_GLPROGRAM_H

namespace LibOpenGL {
	class GLProgram {
	public:
		GLProgram(GLuint vertex, GLuint fragment);
		GLProgram(GLuint vertex, GLuint geom, GLuint fragment);
		GLProgram(GLProgram&& other);
		GLProgram(const GLProgram& other) = delete;
		GLuint ProgramID();
		~GLProgram();
	private:
		GLuint _program;
	};
}

#endif