#ifndef LIBIMAGE_IMAGE_H
#define LIBIMAGE_IMAGE_H
#include <vector>
namespace Image {
	enum class Formats {
		R8B8G8_UNORM,
		R8G8B8A8_UNORM
	};
	struct ImageData {
		Formats format;
		unsigned short width;
		unsigned short height;
		std::vector<unsigned char> data;
	};
	
}

#endif