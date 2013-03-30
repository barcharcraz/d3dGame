#ifndef LIBCOMMON_IRENDERER_H
#define LIBCOMMON_IRENDERER_H
#include "RenderingMessage.h"
namespace LibCommon { 
	//so far just a marker interface
	class IRenderer {
		//virtual RenderingMessage getRenderingMessage() = 0;
		virtual ~IRenderer() = 0;
	};
}
#endif