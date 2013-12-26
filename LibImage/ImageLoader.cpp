#include "ImageLoader.h"
#include <vector>
#include <map>
namespace Image {
	namespace {
		
		ImageCache defaultImageContext;
		ImageCache* activeContext = &defaultImageContext;
	}
	void ImageCache::LoadImage(const std::string& path) {
		auto data = Image::LoadImage(path);
		loaded[path] = std::move(data);

	}
	const ImageData& ImageCache::GetImageData(const std::string& path) {
		if (loaded.count(path) == 0) {
			LoadImage(path);
		}
		return loaded[path];
	}
	const ImageData& GetImageData(const std::string& path) {
		return activeContext->GetImageData(path);
	}
	void ActivateCache(ImageCache* cache) {
		if (cache == nullptr) {
			activeContext = &defaultImageContext;
		} else {
			activeContext = cache;
		}
	}
	void DeactivateCache() {
		ActivateCache(nullptr);
	}
	ImageCache* GetActiveCache() {
		return activeContext;
	}

}