#include "Texture.h"
#include <stdexcept>
namespace Components {
	Texture::Texture(Image::ImageData data)
		: _imageData(std::move(data))
	{
		
	}

	const Image::ImageData& Texture::data() const {
		return _imageData;
	}
	
	
}