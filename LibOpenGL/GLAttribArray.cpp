#include "stdafx.h"
#include "GLAttribArray.h"

namespace LibOpenGL {
	GLAttribArray::GLAttribArray() {
		gl::GenVertexArrays(1, &_vao);
	}
	GLAttribArray::~GLAttribArray() {
		gl::DeleteVertexArrays(1, &_vao);
	}
	GLuint GLAttribArray::AttribArrayID() {
		return _vao;
	}
	void GLAttribArray::Bind() {
		gl::BindVertexArray(_vao);
	}




}