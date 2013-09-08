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
	class ImageFile {
	public:
		virtual Formats Format() const = 0;
		//! \brief This sets the format of the image
		//! note that it DOES NOT rearrange the pixels
		//! so this should only be called when you are
		//! actually doing a format conversion
		virtual void Format(Formats fmt) = 0;
		virtual unsigned short int width() const = 0;
		virtual unsigned short int height() const = 0;
		virtual void width(unsigned short int val) = 0;
		virtual void height(unsigned short int val) = 0;
		virtual std::vector<unsigned char>& data() = 0;
		virtual const std::vector<unsigned char>& data() const = 0;
		operator ImageData() const {
			ImageData rv;
			rv.format = Format();
			rv.height = height();
			rv.width = width();
			rv.data = data(); //this is a copy
			return rv; //this is not a copy
			
		}
		virtual ~ImageFile() {}
			
	};
	
}

#endif
