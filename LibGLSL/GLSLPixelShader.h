#ifndef LIBGLSL_GLSLPIXELSHADER_H
#define LIBGLSL_GLSLPIXELSHADER_H
#include "stdafx.h"
#include <string>
#include <LibEffects/Shader.h>

namespace Effects {
	class GLSLPixelShader {
	public:
		GLSLPixelShader(const std::string& filename, const std::vector<ShaderDesc>& layout);
		~GLSLPixelShader();
		GLuint getShader();
	private:
		void init();
		void loadAndCompile();
		std::string _filename;
		std::vector<ShaderDesc> _layout;
		GLuint _shader;
	};
}

#endif
