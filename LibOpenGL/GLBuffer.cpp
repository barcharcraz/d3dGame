#include "stdafx.h"
#include "GLBuffer.h"
#include <iostream>
namespace LibOpenGL {
	GLBuffer::GLBuffer() {
		init();
	}
	GLBuffer::GLBuffer(GLenum target) {
		init();

		initalTarget = target;
	}
	GLBuffer::GLBuffer ( GLBuffer && other ) {
		currentSize = other.currentSize;
		initalTarget = other.initalTarget;
		lastUsage = other.lastUsage;
		_buffer = other._buffer;
		other._buffer = 0;
		
	}

	GLBuffer::~GLBuffer() {
		//this check is not strictly required
		//but it increases clarity and prevents
		//the call that would do nothing
		if(_buffer != 0) {
			gl::DeleteBuffers(1, &_buffer);
		}

	}
	//PUBLIC UPDATE METHODS
	void GLBuffer::UpdateData(GLenum target, GLsizeiptr size, const void *data, GLenum usage) {
		if(target != initalTarget) {
			std::cerr << "Warning - performence: updated buffer with a different target than it was created with" << std::endl;
			initalTarget = target;
		}
		GLint boundTarget = 0;
		gl::GetIntegerv(gl::VERTEX_ARRAY_BINDING, &boundTarget);
		if(static_cast<unsigned int>(boundTarget) != _buffer) {
			gl::BindBuffer(target, _buffer);
		}
		if(currentSize != size) {
			gl::BufferData(target, size, data, usage);
			currentSize = size;
			return;
		}
		if(usage != lastUsage) {
			std::cerr << "Warning - performence: changed usage on update, reallocateing buffer" << std::endl;
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
	GLuint GLBuffer::GetBuffer() {
		return _buffer;
	}

	void GLBuffer::init() {
		currentSize = 0;
		lastUsage = 0;
		initalTarget = 0;
		gl::GenBuffers(1, &_buffer);
	}
}
