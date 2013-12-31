#ifndef LIBCOMPONENTS_TEXTURE_H
#define LIBCOMPONENTS_TEXTURE_H
#include "IComponent.h"
#include <LibImage/image.h>
namespace Components {
	class Texture : public IComponent {
	public:
		Texture(Image::ImageData& data);
		const Image::ImageData& data() const;
		Image::ImageData& data();
	private:
		Image::ImageData& _imageData;
	};
}

#endif
