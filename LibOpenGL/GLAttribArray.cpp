#include "stdafx.h"
#include "GLAttribArray.h"

namespace LibOpenGL {
	GLAttribArray::GLAttribArray() {
		_vao = 0;
		gl::GenVertexArrays(1, &_vao);
	}
	GLAttribArray::GLAttribArray ( GLAttribArray && other ) {
		_vao = other._vao;
		other._vao = 0;
		
	}

	GLAttribArray::~GLAttribArray() {
		if(_vao != 0) {
			gl::DeleteVertexArrays(1, &_vao);
		}
	}
	GLuint GLAttribArray::name() {
		return _vao;
	}
	void GLAttribArray::Bind() {
		gl::BindVertexArray(_vao);
	}




}
