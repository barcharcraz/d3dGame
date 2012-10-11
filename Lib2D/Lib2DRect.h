#pragma once
#include "ilib2dshape.h"
class Lib2DRect :
	public ILib2DShape
{
public:
	Lib2DRect(D2D1_RECT_F rect, ID2D1Brush * brush, bool fill = false);
	virtual void draw(ID2D1DeviceContext* pContext);
	~Lib2DRect(void);
private:
	D2D1_RECT_F m_rect;
	ID2D1Brush * m_brush;
	bool m_fill;
};

