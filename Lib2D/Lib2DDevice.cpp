#include "stdafx.h"
#include "Lib2DDevice.h"


Lib2DDevice::Lib2DDevice(ID2D1Device *device)
{
	m_device = device;
}


Lib2DDevice::~Lib2DDevice(void)
{
}
