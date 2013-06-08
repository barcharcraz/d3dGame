#include "Direct2DBitmap.h"
#include <LibCommon/IComponent.h>
namespace LibDirect2D {
	Direct2DBitmap::Direct2DBitmap(std::wstring file) 
		: filename(file) 
	{
		BIND(HandleDraw, Direct2DRenderingMessage);
	}
}