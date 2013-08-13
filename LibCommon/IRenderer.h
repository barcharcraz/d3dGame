#ifndef LIBCOMMON_IRENDERER_H
#define LIBCOMMON_IRENDERER_H
#include "IRenderingMessage.h"
namespace LibCommon { 
	//so far just a marker interface
	class IRenderer {
	public:
		virtual ~IRenderer()= 0;
	};
	
	//need this for GCC and standards complience
	inline IRenderer::~IRenderer() {}
}
#endif
