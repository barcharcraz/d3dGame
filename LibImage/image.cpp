#include "image.h"
#include <Utils/files.h>
#include <Utils/exceptions.h>
#include "targa.h"
namespace Image {
	ImageData LoadImage(const std::string& filename) {
		std::string ext = utils::getFileExtension(filename);
		if (ext == "tga") {
			//targa file
			auto tgaData = Targa::LoadTarga(filename);
			return ImageData(tgaData);
		}
		throw utils::not_supported_error("the extension: " + ext + " is not supported");
	}
}