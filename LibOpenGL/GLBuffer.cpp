#include "stdafx.h"
#include "GLBuffer.h"
#include <iostream>
namespace LibOpenGL {
	GLBuffer::GLBuffer() {
		init();
	}
	GLBuffer::GLBuffer(GLenum target) {
		init();
		gl::BindBuffer(target, _buffer);

		initalTarget = target;
	}

	GLBuffer::~GLBuffer() {
		gl::DeleteBuffers(1, &_buffer);

	}
	//PUBLIC UPDATE METHODS
	void GLBuffer::UpdateData(GLenum target, GLsizeiptr size, const void *data, GLenum usage) {
		if(target != initalTarget) {
			std::cerr << "Warning - performence: updated buffer with a different target than it was created with";
		}
		GLint boundTarget = 0;
		gl::GetIntegerv(gl::VERTEX_ARRAY_BINDING, &boundTarget);
		if(boundTarget != _buffer) {
			gl::BindBuffer(target, _buffer);
		}
		if(currentSize != size) {
			gl::BufferData(target, size, data, usage);
			currentSize = size;
			return;
		}
		if(usage != lastUsage) {
			std::cerr << "Warning - performence: changed usage on update, reallocateing buffer";
			gl::BufferData(target, size, data, usage);
			lastUsage = usage;
			currentSize = size;
			return;
		}
		
		gl::BufferSubData(target, 0, size, data);


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
		gl::GenBuffers(1, &_buffer);
	}
}
