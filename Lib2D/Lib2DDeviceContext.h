#pragma once
#include <atlbase.h>
class Lib2DDeviceContext
{
public:
	Lib2DDeviceContext(ID2D1DeviceContext * context);
	void setTarget(IDXGISurface * target);
	~Lib2DDeviceContext(void);
private:
	CComPtr<ID2D1DeviceContext> m_context;
};

