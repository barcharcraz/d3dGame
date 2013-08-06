#include "stdafx.h"
#include "conversions.h"
#include "image.h"
#include <climits>
namespace Image {
	namespace Conversions {
		ImageData R8G8B8_UNORM_to_R8G8B8A8_UNORM(const ImageData& dat) {
			ImageData retval;
			retval.format = Formats::R8G8B8A8_UNORM;
			retval.height = dat.height;
			retval.width = dat.width;
			unsigned int newSize = 4 * retval.width * retval.height;
			retval.data.resize(newSize, 0);
			for(unsigned int i = 0, j = 0; i < dat.data.size() && j < retval.data.size(); i += 3, j += 4) {
				//we copy three bytes from the input, then set the 4th to 1
				retval.data[j + 0] = dat.data[i + 0];
				retval.data[j + 1] = dat.data[i + 1];
				retval.data[j + 2] = dat.data[i + 2];
				retval.data[j + 3] = UCHAR_MAX;
			}
			return retval;
		}
		ImageData R8G8B8A8_UNORM_to_R8G8B8_UNORM(const ImageData &dat) {
			ImageData retval;
			retval.format = Formats::R8G8B8_UNORM;
			retval.height = dat.height;
			retval.width = dat.width;
			unsigned int newSize = 3 * retval.width * retval.height;
			retval.data.resize(newSize, 0);
			for(unsigned int i = 0, j = 0; i < dat.data.size() && j < dat.data.size(); i += 4, j += 3) {
				retval.data[j + 0] = dat.data[i + 0];
				retval.data[j + 1] = dat.data[i + 1];
				retval.data[j + 2] = dat.data[i + 2];
				//and we ignore the alpha value
			}
			return retval;
		}

		ImageData ConvertToR8G8B8A8_UNORM(const ImageData &dat) {
			switch(dat.format) {
			case Formats::R8G8B8_UNORM:
				return R8G8B8_UNORM_to_R8G8B8A8_UNORM(dat);
			case Formats::R8G8B8A8_UNORM:
				return dat; //this is a copy
			}
		}
		ImageData ConvertToR8B8G8_UNORM(const ImageData &dat) {
			switch(dat.format) {
			case Formats::R8G8B8_UNORM:
				return dat;
			case Formats::R8G8B8A8_UNORM:
				return R8G8B8A8_UNORM_to_R8G8B8_UNORM(dat);
			}
		}

		ImageData ConvertImage(const ImageData &dat, Formats fmt) {
			switch(fmt) {
			case Formats::R8G8B8_UNORM:
				return ConvertToR8B8G8_UNORM(dat);
			case Formats::R8G8B8A8_UNORM:
				return ConvertToR8G8B8A8_UNORM(dat);
			}
		}
	}
}
