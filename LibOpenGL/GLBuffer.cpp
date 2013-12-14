#include "stdafx.h"
#include "GLBuffer.h"
#include <iostream>
namespace LibOpenGL {
	GLBuffer::GLBuffer() {
		init();
	}
	GLBuffer::GLBuffer(GLenum target) {
		init();

		initialTarget = target;
	}
	GLBuffer::GLBuffer ( GLBuffer && other ) {
		currentSize = other.currentSize;
		initialTarget = other.initialTarget;
		lastUsage = other.lastUsage;
		_buffer = other._buffer;
		other._buffer = 0;
		
	}

	GLBuffer::~GLBuffer() {
		//this check is not strictly required
		//but it increases clarity and prevents
		//the call that would do nothing
        //Also, apperently there are errors with
        //some drivers here
		if(_buffer != 0) {
			gl::DeleteBuffers(1, &_buffer);
		}

	}
	bool GLBuffer::HasData() {
		if (currentSize == 0) {
			return false;
		} else {
			return true;
		}
	}
	//PUBLIC UPDATE METHODS
    void GLBuffer::Allocate(GLenum target, GLsizeiptr size, GLenum usage) {
        if(target != initialTarget) {
            fprintf(stderr, "Warning - performence: updated buffer"
                            "with a differend target than it was "
                            "created with");
        }
        gl::BindBuffer(target, _buffer);
        currentSize = size;
        lastUsage = usage; 
        gl::BufferData(target, size, nullptr, usage);
        gl::BindBuffer(target, 0);
    }
    void GLBuffer::AllocateOnce(GLenum target, GLsizeiptr size, GLenum usage) {
        if(this->HasData()) {
            //already initialized
            return;
        }
        this->Allocate(target, size, usage);
        
    }
	void GLBuffer::UpdateData(GLenum target, GLsizeiptr size, const void *data, GLenum usage) {
		if(target != initialTarget) {
			std::cerr << "Warning - performence: updated buffer with a different target than it was created with" << std::endl;
			initialTarget = target;
		}
		gl::BindBuffer(target, _buffer);
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
		UpdateData(initialTarget, size, data, usage);
	}
	GLuint GLBuffer::GetBuffer() {
		return _buffer;
	}

	void GLBuffer::init() {
		currentSize = 0;
		lastUsage = 0;
		initialTarget = 0;
		gl::GenBuffers(1, &_buffer);
	}
}
