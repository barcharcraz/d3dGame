#include "stdafx.h"
#include <string>
#ifndef LIBOPENGL_GLSHADER_H
#define LIBOPENGL_GLSHADER_H

namespace LibOpenGL {
	class GLShader {
		GLShader(GLenum type, const std::string& filename);
		
	private:
		GLenum _type;
		GLuint _shader;
	};
}

#endif