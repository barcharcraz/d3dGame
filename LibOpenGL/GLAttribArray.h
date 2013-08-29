#include "stdafx.h"
#ifndef LIBOPENGL_GLATTRIBARRAY_H
#define LIBOPENGL_GLATTRIBARRAY_H

namespace LibOpenGL {
	class GLAttribArray {
		public:
			GLAttribArray();
			GLuint AttribArrayID();
			void Bind();
			~GLAttribArray();
	private:
		GLuint _vao;
		
	};
}

#endif