#ifndef LIBCOMPONENTS_TEXTURE_H
#define LIBCOMPONENTS_TEXTURE_H
#include <ecs.h>
#include <LibImage/image.h>
namespace Components {
	class Texture : public sparse::ecs::Component {
	public:
		static sparse::ecs::ComponentInfo sinfo;
		Texture(Image::ImageData data);
		const Image::ImageData& data() const;
		Image::ImageData& data();
	private:
		Image::ImageData _imageData;
	};
}

#endif