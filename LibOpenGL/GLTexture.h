
#ifndef LIBOPENGL_GLTEXTURE_H
#define LIBOPENGL_GLTEXTURE_H
#include "stdafx.h"
#include "GLProgram.h"
#include <LibImage/image.h>
#include <Utils/cache.h>
#include <unordered_map>
namespace LibOpenGL {
	//! \brief RAII handle to a openGL texture object
	//! this is a non-copyable class
	class GLTexture {
	public:
		GLTexture();
		GLTexture(Image::ImageData* image);
		GLTexture(const GLTexture& other) = delete;
		GLTexture(GLTexture&& other);

		GLTexture& operator=(GLTexture&& other);
		GLTexture& operator=(const GLTexture& other) = delete;

		void Bind();
        GLuint GLObject();
		~GLTexture();
	private:
		void init();
		GLuint _texture;
		Image::ImageData* _image = nullptr;
	};
	//! \brief Upload an image to an openGL texture
	//!
	//! This function allocates and uploads an image to a mutable
	//! texture.
	void SetTexImage(GLuint texture, const Image::ImageData& dat);


	//! \brief Get the internal format corresponding to the
	//! fmt param
	//! \param fmt the format of the image
	GLint GetInternalFormat(Image::Formats fmt);
	GLenum GetFormat(Image::Formats fmt);
	GLenum GetType(Image::Formats fmt);
}

#endif
