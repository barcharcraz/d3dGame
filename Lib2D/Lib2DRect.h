#pragma once
#include "Lib2DShape.h"
#include <atlbase.h>
class Lib2DRect :
	public Lib2DShape
{
public:
	Lib2DRect(D2D1_RECT_F rect, CComPtr<ID2D1Brush> brush, bool fill = false);
	virtual void draw(ID2D1DeviceContext* pContext);
	~Lib2DRect(void);
private:
	D2D1_RECT_F m_rect;
	CComPtr<ID2D1Brush> m_brush;
	bool m_fill;
};

