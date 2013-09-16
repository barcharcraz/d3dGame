#include "stdafx.h"
#ifndef LIBOPENGL_GLATTRIBARRAY_H
#define LIBOPENGL_GLATTRIBARRAY_H

namespace LibOpenGL {
	class GLAttribArray {
		public:
			GLAttribArray();
			GLAttribArray(const GLAttribArray& other) = delete;
			GLAttribArray(GLAttribArray&& other);
			GLuint name();
			void Bind();
			~GLAttribArray();
	private:
		GLuint _vao;
		
	};
}

#endif
