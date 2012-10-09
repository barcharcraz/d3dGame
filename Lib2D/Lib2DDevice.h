#pragma once
#include <d2d1_1.h>
#include <atlbase.h>
class Lib2DDevice
{
public:
	Lib2DDevice(ID2D1Device *device);
	~Lib2DDevice(void);
private:
	CComPtr<ID2D1Device> m_device;
};

