#ifndef LIBCOMPONENTS_TEXTURE_H
#define LIBCOMPONENTS_TEXTURE_H
#include "IComponent.h"
#include <LibImage/image.h>
#include <RenderingUtils/TextureFunctions.h>
namespace Components {
	class Texture : public IComponent {
	public:
        
		Texture(const Image::ImageData& data, utils::tex::texture_type_e tex_type = utils::tex::TEXTURE2D);
		const Image::ImageData& data() const;
        utils::tex::texture_type_e type;
	private:
		const Image::ImageData* _imageData;
	};
}

#endif
