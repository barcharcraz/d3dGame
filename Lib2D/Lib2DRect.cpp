#include "stdafx.h"
#include "Lib2DRect.h"


Lib2DRect::Lib2DRect(D2D1_RECT_F rect, ID2D1Brush * brush, bool fill) : m_rect(rect), m_brush(brush), m_fill(fill)
{
}


Lib2DRect::~Lib2DRect(void)
{
}

void Lib2DRect::draw( ID2D1DeviceContext* pContext )
{
	if(m_fill) {
		pContext->FillRectangle(&m_rect, m_brush);
	} else {
		pContext->DrawRectangle(&m_rect, m_brush);
	}
}