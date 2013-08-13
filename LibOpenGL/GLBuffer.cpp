#include "stdafx.h"
#include "GLBuffer.h"
#include <iostream>
namespace LibOpenGL {
	GLBuffer::GLBuffer() {
		init();
	}
	GLBuffer::GLBuffer(GLenum target) {
		init();
		glBindBuffer(target, _buffer);
		initalTarget = target;
	}

	GLBuffer::~GLBuffer() {
		glDeleteBuffers(1, &_buffer);
	}
	//PUBLIC UPDATE METHODS
	void GLBuffer::UpdateData(GLenum target, GLsizeiptr size, const void *data, GLenum usage) {
		if(target != initalTarget) {
			std::cerr << "Warning - performence: updated buffer with a different target than it was created with";
		}
		GLint boundTarget = 0;
		glGetIntegerv(GL_VERTEX_ARRAY_BUFFER_BINDING, &boundTarget);
		if(boundTarget != _buffer) {
			glBindBuffer(target, _buffer);
		}
		if(currentSize != size) {
			glBufferData(target, size, data, usage);
			currentSize = size;
			return;
		}
		if(usage != lastUsage) {
			std::cerr << "Warning - performence: changed usage on update, reallocateing buffer";
			glBufferData(target, size, data, usage);
			lastUsage = usage;
			currentSize = size;
			return;
		}
		glBufferSubData(target, 0, size, data);


	}
	void GLBuffer::UpdateData(GLenum target, GLsizeiptr size, const void *data) {
		UpdateData(target, size, data, lastUsage);
	}
	void GLBuffer::UpdateData(GLsizeiptr size, const void *data, GLenum usage) {
		UpdateData(initalTarget, size, data, usage);
	}

	void GLBuffer::init() {
		currentSize = 0;
		lastUsage = 0;
		glGenBuffers(1, &_buffer);
	}
}
