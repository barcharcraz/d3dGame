#include "stdafx.h"
#include <LibImage/image.h>
#ifndef LIBOPENGL_GLTEXTURE_H
#define LIBOPENGL_GLTEXTURE_H

namespace LibOpenGL {
	class GLTexture {

	};
	void SetTexImage(GLuint texture, const Image::ImageData dat);
	GLint GetInternalFormat(Image::Formats fmt);
	GLenum GetFormat(Image::Formats fmt);
	GLenum GetType(Image::Formats fmt);
}

#endif