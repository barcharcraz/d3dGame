#pragma once
#include <d2d1_1.h>
class ILib2DShape {
public:
	virtual void draw(ID2D1DeviceContext* pContext) = 0;
};