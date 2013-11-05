#include "GLTexture.h"
#include <Utils/exceptions.h>
namespace LibOpenGL {
	GLTexture::GLTexture() {
		init();
	}
	GLTexture::GLTexture(GLTexture&& other) {
		*this = std::move(other);
	}
	GLTexture& GLTexture::operator=(GLTexture&& other) {
		_texture = other._texture;
		_image = other._image;
		other._image = nullptr;
		other._texture = 0;
		return *this;
	}
	GLTexture::GLTexture(Image::ImageData* image)
		: _image(image) 
	{
		init();
		SetTexImage(_texture, *_image);
	}

	GLTexture::~GLTexture() {
		gl::DeleteTextures(1, &_texture);
	}
    
    void GLTexture::Bind() {
        gl::ActiveTexture(gl::TEXTURE0);
        gl::BindTexture(gl::TEXTURE_2D, _texture);
    }

   	void GLTexture::init() {
		gl::GenTextures(1, &_texture);
	}

	//freestanding functions
	void SetTexImage(GLuint texture, const Image::ImageData& dat) {
		gl::ActiveTexture(gl::TEXTURE0);
		gl::BindTexture(gl::TEXTURE_2D, texture);
		gl::TexImage2D(gl::TEXTURE_2D, 0,
			GetInternalFormat(dat.format),
			dat.width,
			dat.height,
			0, GetFormat(dat.format),
			GetType(dat.format),
			&dat.data[0]
			);
		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_BASE_LEVEL, 0);
		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAX_LEVEL, 0);
	}
	GLint GetInternalFormat(Image::Formats fmt) {
		switch (fmt) {
		case Image::Formats::R8G8B8A8_UNORM:
			return gl::RGBA8;
		case Image::Formats::R8G8B8_UNORM:
			return gl::RGB8;
        default:
            throw utils::unsupported_format_error("format is not supported");
		}
		
	}
	GLenum GetFormat(Image::Formats fmt) {
		switch (fmt) {
		case Image::Formats::R8G8B8_UNORM:
			return gl::RGB;
		case Image::Formats::R8G8B8A8_UNORM:
			return gl::RGBA;
        default:
            throw utils::unsupported_format_error("format is not supported");
		}
		
	}
	GLenum GetType(Image::Formats fmt) {
		switch (fmt) {
		case Image::Formats::R8G8B8_UNORM:
			return gl::UNSIGNED_BYTE;
		case Image::Formats::R8G8B8A8_UNORM:
			return gl::UNSIGNED_BYTE;
		case Image::Formats::A8R8G8B8_UNORM:
			return gl::UNSIGNED_BYTE;
        default:
            throw utils::unsupported_format_error("unknown format");
		}
	}
}
