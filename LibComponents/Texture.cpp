#include "Texture.h"
#include <stdexcept>
namespace Components {
	Texture::Texture(const Image::ImageData& data, utils::tex::texture_type_e tex_type)
        : _imageData(&data), type(tex_type)
	{
		
	}

	const Image::ImageData& Texture::data() const {
		return *_imageData;
	}
	
	
}
