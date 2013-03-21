#pragma once
#include <Unknwn.h>
namespace LibCommon {
	class IShape {
	public:
		virtual void draw(IUnknown* pContext);
	};
}