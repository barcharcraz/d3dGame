#ifndef LIBOPENGL_GLBUFFER_H
#define LIBOPENGL_GLBUFFER_H
#include "stdafx.h"
namespace LibOpenGL {
	class GLBuffer {
	public:
		GLBuffer();
		GLBuffer(GLenum target);
		GLBuffer(const GLBuffer& other) = delete;
		GLBuffer(GLBuffer&& other);
		bool HasData();
		void UpdateData(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
		void UpdateData(GLenum target, GLsizeiptr size, const void *data);
		void UpdateData(GLsizeiptr size, const void *data, GLenum usage);
		GLuint GetBuffer();
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
