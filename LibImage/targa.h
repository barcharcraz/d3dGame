#ifndef LIBIMAGE_TARGA_H
#define LIBIMAGE_TARGA_H
#include <vector>
namespace Image {
	namespace Targa {
		enum ColorMapType : unsigned char {
			NO_COLOR_MAP = 0,
			HAS_COLOR_MAP = 1
		};
		enum ImageType : unsigned char {
			NO_IMAGE_DATA = 0,
			UNCOMPRESSED_COLOR_MAP = 1,
			UNCOMPRESSED_TRUE_COLOR = 2,
			UNCOMPRESSED_GREYSCALE = 3,
			RLE_COLOR_MAP = 9,
			RLE_TRUE_COLOR = 10,
			RLC_GREYSCALE = 11
		};
		//! \brief this enum is the position of the first
		//!        pixel in the image, the values of this enum
		//!        are the same as those defined in the TARGA spec
		enum ImageOrigin : unsigned char {
			BOTTOM_LEFT = 0x00,
			BOTTOM_RIGHT = 0x10,
			TOP_LEFT = 0x20,
			TOP_RIGHT = 0x30
		};
		struct ColorMapSpec {
			unsigned short offset;
			unsigned short length;
			unsigned char bpp;
		};
		struct ImageSpec {
			unsigned short x_origin;
			unsigned short y_origin;
			unsigned short width;
			unsigned short height;
			unsigned char pixel_depth;
			unsigned char alpha_depth;
			ImageOrigin origin;

		};
		struct TargaFile {
			unsigned char ID_len;
			ColorMapType color_map_type;
			ImageType image_type;
			ColorMapSpec color_map_spec;
			ImageSpec image_spec;
			std::vector<unsigned char> color_map_data;
			std::vector<unsigned char> image_data;
		};
		TargaFile LoadTarga(const std::string& filename);
	}
}

#endif