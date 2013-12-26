#ifndef LIBIMAGE_IMAGELOADER_H
#define LIBIMAGE_IMAGELOADER_H
#include "image.h"
#include <string>
#include <map>
namespace Image {
	struct ImageCache {
		void LoadImage(const std::string& path);
		const ImageData& GetImageData(const std::string& path);
	private:
		std::map<std::string, ImageData> loaded;
	};
	const ImageData& GetImageData(const std::string& path);
	void ActivateCache(ImageCache* cache);
	void DeactivateCache();
	ImageCache* GetActiveCache();
}

#endif