#include "stdafx.h"
#include <string>
#include <LibImage/image.h>
#ifndef LIBOPENGL_GLUNIFORMS_H
#define LIBOPENGL_GLUNIFORMS_H

namespace LibOpenGL {
	void BindTexture(GLuint program, const std::string& name, 
		const Image::ImageData& dat);
}

#endif