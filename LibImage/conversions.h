#ifndef LIBIMAGE_CONVERSIONS_H
#define LIBIMAGE_CONVERSIONS_H
#include "image.h"
namespace Image {
	namespace Conversions {
		ImageData R8G8B8_UNORM_to_R8G8B8A8_UNORM(const ImageData& dat);
		ImageData R8G8B8A8_UNORM_to_R8G8B8_UNORM(const ImageData& dat);
		ImageData ConvertToR8G8B8A8_UNORM(const ImageData& dat);
		ImageData ConvertToR8B8G8_UNORM(const ImageData& dat);
		ImageData ConvertImage(const ImageData& dat, Formats fmt);
	}
}

#endif
