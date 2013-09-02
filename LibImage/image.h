#ifndef LIBIMAGE_IMAGE_H
#define LIBIMAGE_IMAGE_H
#include <vector>
#include <string>
namespace Image {

	enum class Formats {
		R8G8B8_UNORM,
		R8G8B8A8_UNORM,
		A8R8G8B8_UNORM
	};
	struct ImageData {
		Formats format;
		unsigned short width;
		unsigned short height;
		std::vector<unsigned char> data;
	};
	ImageData LoadImage(const std::string& filename);
	
}

#endif
