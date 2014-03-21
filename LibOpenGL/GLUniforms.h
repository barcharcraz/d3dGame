#ifndef LIBOPENGL_GLUNIFORMS_H
#define LIBOPENGL_GLUNIFORMS_H
#include "stdafx.h"
#include <string>
#include <LibImage/image.h>
#include <LibCommon/Data.h>
namespace Components {
	class Material;
}

namespace LibOpenGL {
	void BindTexture(GLuint program, const std::string& name, 
		const Image::ImageData& dat);
	void BindMaterial(GLuint program, const std::string& name, 
		const Components::Material& mat);
	void BindMVP(GLuint program, const LibCommon::Transforms& trans,
		const std::string& name);
}

#endif