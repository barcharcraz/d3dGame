#include "Texture.h"
#include <stdexcept>
namespace Components {
	Texture::Texture(Image::ImageData& data)
		: _imageData(data)
	{
		
	}

	const Image::ImageData& Texture::data() const {
		return _imageData;
	}
	Image::ImageData& Texture::data() {
		return _imageData;
	}
	
	
}
