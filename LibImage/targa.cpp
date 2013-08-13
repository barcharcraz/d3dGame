#include "stdafx.h"
#include "targa.h"
#include "image.h"
#include <Utils/exceptions.h>
#include <fstream>
namespace Image {
	namespace Targa {
		static void ValidateTarga(const TargaFile& file);
		
		TargaFile LoadTarga(const std::string& filename) {
			using std::ifstream;
			using std::ios;
			TargaFile retval;
			ifstream file(filename, ios::in | ios::binary);
			if (!file.is_open()) {
				throw utils::not_found_error(filename);
			}
			file.read((char*) (&retval.ID_len), 1);
			file.read((char*) (&retval.color_map_type), 1);
			file.read((char*) (&retval.image_type), 1);
			file.read((char*) (&retval.color_map_spec.offset), 2);
			file.read((char*) (&retval.color_map_spec.length), 2);
			file.read((char*) (&retval.color_map_spec.bpp), 1);
			file.read((char*) (&retval.image_spec.x_origin), 2);
			file.read((char*) (&retval.image_spec.y_origin), 2);
			file.read((char*) (&retval.image_spec.width), 2);
			file.read((char*) (&retval.image_spec.height), 2);
			file.read((char*) (&retval.image_spec.pixel_depth), 1);
			unsigned char descriptor = 0;
			file.read((char*) (&descriptor), 1);
			//mask to get the bits of the alpha
			//this is 0b00001111
			unsigned char alpha_mask = 0x0F;
			//this is 0b00110000
			unsigned char order_mask = 0x30;
			unsigned char alpha = descriptor & alpha_mask;
			unsigned char order = descriptor & order_mask;
			retval.image_spec.alpha_depth = alpha;
			retval.image_spec.origin = (ImageOrigin)order;
			ValidateTarga(retval); //makes sure our header is of a supported type
			std::vector<char> image_id_field(retval.ID_len);
			retval.color_map_data.resize(retval.color_map_spec.length * retval.color_map_spec.bpp, 0);
			if (retval.color_map_spec.length > 0) {
				file.seekg(retval.color_map_spec.offset);
				file.read((char*) (&retval.color_map_data[0]), retval.color_map_spec.length * (retval.color_map_spec.bpp / 8));
			}
			//size in bytes of the image data
			int image_size = retval.image_spec.width * retval.image_spec.height * (retval.image_spec.pixel_depth/8);
			retval.image_data.resize(image_size, 0);
			file.read((char*) (&retval.image_data[0]), image_size);
			if (retval.image_spec.origin == BOTTOM_RIGHT) {
				std::reverse(retval.image_data.begin(), retval.image_data.end());
			}
			if (retval.image_spec.origin == BOTTOM_LEFT) {
				for (unsigned int i = 0; i < retval.image_spec.height; ++i) {
					auto lineStart = retval.image_data.begin() += i * retval.image_spec.width * (retval.image_spec.pixel_depth / 8);
					auto lineEnd = retval.image_data.begin() += (i + 1) * retval.image_spec.width * (retval.image_spec.pixel_depth / 8);
					std::reverse(lineStart, lineEnd);
				}
			}
			return retval;

		}
		void ValidateTarga(const TargaFile& file) {
			if (file.color_map_type != NO_COLOR_MAP) {
				throw utils::not_supported_error("Color Mapped targa files are not supported");
			}
			if (file.image_type != UNCOMPRESSED_TRUE_COLOR && file.image_type != UNCOMPRESSED_GREYSCALE) {
				throw utils::not_supported_error("only uncompressed targa files are supported");
			}

		}
		TargaFile::operator Image::ImageData() {
			ImageData retval;
			if (this->image_spec.pixel_depth == 24 && this->image_spec.alpha_depth == 0) {
				retval.format = Formats::R8G8B8_UNORM;
			} else if (this->image_spec.pixel_depth == 32 && this->image_spec.alpha_depth == 8) {
				retval.format = Formats::R8G8B8A8_UNORM;
			} else {
				throw utils::not_supported_error("TARGA piexl format not supported");
			}
			retval.width = this->image_spec.width;
			retval.height = this->image_spec.height;
			retval.data = this->image_data; //this is a copy
			return retval;
		}
	}
}
