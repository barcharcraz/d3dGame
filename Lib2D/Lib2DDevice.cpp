#include "stdafx.h"
#include "Lib2DDevice.h"


Lib2DDevice::Lib2DDevice(ID2D1Device *device)
{
	m_device = device;
}


Lib2DDevice::~Lib2DDevice(void)
{
}

std::shared_ptr<Lib2DDeviceContext> Lib2DDevice::getContext()
{
	if(!m_context) {
		ID2D1DeviceContext * context;
		HRESULT hr;
		hr = m_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &context);
		m_context = context;
	}
	Lib2DDeviceContext * l2dContext = new Lib2DDeviceContext(m_context);
	std::shared_ptr<Lib2DDeviceContext> retval(l2dContext);
	return retval;
}
