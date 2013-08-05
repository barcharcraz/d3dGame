#include "stdafx.h"
#include "targa.h"
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

		}
		void ValidateTarga(const TargaFile& file) {
			
		}
	}
}