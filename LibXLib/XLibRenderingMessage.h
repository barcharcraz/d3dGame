#ifndef LIBXLIB_XLIBRENDERINGMESSAGE_H
#define LIBXLIB_XLIBRENDERINGMESSAGE_H
#include <X11/Xlib.h>

#include <LibCommon/RenderingMessage.h>
namespace LibXLib {
	class XLibRenderingMessage : public RenderingMessage {
		Display &pXDisplay;
	}
}

#endif
