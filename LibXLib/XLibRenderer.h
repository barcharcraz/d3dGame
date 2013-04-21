#ifndef LIBXLIB_XLIBRENDERER_H
#define LIBXLIB_XLIBRENDERER_H

#include <LibCommon/IRenderer.h>
namespace LibXLib {
	class XLibRenderer : public IRenderer {
		virtual const XLibRenderingMessage* const getRenderingMessage() override;
	} 
}

#endif
