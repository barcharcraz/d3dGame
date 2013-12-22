#include "Texture.h"
#include <stdexcept>
namespace Components {
	sparse::ecs::ComponentInfo Texture::sinfo = sparse::ecs::GenDefCompInfo<Texture>();
	Texture::Texture(Image::ImageData data)
		: _imageData(std::move(data))
	{
		info = &Texture::sinfo;
	}

	const Image::ImageData& Texture::data() const {
		return _imageData;
	}
	Image::ImageData& Texture::data() {
		return _imageData;
	}
	
	
}