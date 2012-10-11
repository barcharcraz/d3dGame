#pragma once
#include <d2d1_1.h>
#include <atlbase.h>
#include <memory>
#include "Lib2DDeviceContext.h"
class Lib2DDevice
{
public:
	Lib2DDevice(ID2D1Device *device);
	std::shared_ptr<Lib2DDeviceContext> getContext();
	~Lib2DDevice(void);
private:
	CComPtr<ID2D1Device> m_device;
	CComPtr<ID2D1DeviceContext> m_context;
};

