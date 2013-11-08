#include "stdafx.h"
#include <string>
#include <vector>
#include <sstream>
#include <Utils/preprocess.h>
#ifndef LIBOPENGL_GLSHADER_H
#define LIBOPENGL_GLSHADER_H

namespace LibOpenGL {
	class GLShader {
	public:
		GLShader(GLenum type, const std::string& filename);
		~GLShader();
		void SetDefine(std::string define, std::string value);
		void SetDefine(std::string define, int value);
        void SetDefine(std::string define);
		GLuint ShaderID();
		GLenum ShaderType();
		void Compile();
	private:
        
        std::string shader_src;
		GLenum _type;
		GLuint _shader;
	};
    
}

#endif
