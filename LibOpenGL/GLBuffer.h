#ifndef LIBOPENGL_GLBUFFER_H
#define LIBOPENGL_GLBUFFER_H
#include "stdafx.h"
namespace LibOpenGL {
	class GLBuffer {
	public:
		GLBuffer();
		GLBuffer(GLenum target);
		void UpdateData(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
		void UpdateData(GLenum target, GLsizeiptr size, const void *data);
		void UpdateData(GLsizeiptr size, const void *data, GLenum usage);
		~GLBuffer();
	private:
		GLenum lastUsage;
		GLenum initalTarget;
		GLsizeiptr currentSize;
		void init();
		GLuint _buffer;
	};
}

#endif
