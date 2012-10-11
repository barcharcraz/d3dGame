#pragma once
#include <atlbase.h>
#include <d2d1_1.h>
#include <vector>
#include "ILib2DShape.h"
class Lib2DDeviceContext
{
public:
	Lib2DDeviceContext(ID2D1DeviceContext * context);
	void setTarget(IDXGISurface * target);
	CComPtr<ID2D1SolidColorBrush> GetSolidColorBrush(D2D1::ColorF color);
	void DrawShapes(std::vector<ILib2DShape*> shapes);
	~Lib2DDeviceContext(void);
private:
	CComPtr<ID2D1DeviceContext> m_context;
};

