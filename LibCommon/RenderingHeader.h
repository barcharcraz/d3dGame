#ifndef LIBCOMMON_RENDERINGHEADER_H
#define LICOMMON_RENDERINGHEADER_H
#include "IMessageHeader.h"
namespace LibCommon {
	enum APITypes {
		DIRECT3D11_1,
		DIRECT2D1_1,
		OPENGL
	};
	class RenderingHeader : public IMessageHeader {
	public:
		RenderingHeader();
		APITypes RenderingAPI;
	};
}
#endif