#include "stdafx.h"
#include <string>
#include <LibImage/image.h>

#ifndef LIBOPENGL_GLUNIFORMS_H
#define LIBOPENGL_GLUNIFORMS_H

namespace Components {
	class Material;
}

namespace LibOpenGL {
	void BindTexture(GLuint program, const std::string& name, 
		const Image::ImageData& dat);
	void BindMaterial(GLuint program, const std::string& name, 
		const Components::Material& mat);
}

#endif