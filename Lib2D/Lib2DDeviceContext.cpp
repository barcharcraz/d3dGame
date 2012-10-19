#include "stdafx.h"
#include "Lib2DDeviceContext.h"
#include <d2d1helper.h>
#include <iostream>


Lib2DDeviceContext::Lib2DDeviceContext(ID2D1DeviceContext * context)
{
	m_context.Attach(context);
}


Lib2DDeviceContext::~Lib2DDeviceContext(void)
{
}

void Lib2DDeviceContext::setTarget( IDXGISurface * target )
{
	CComPtr<ID2D1Bitmap1> targetBitmap;
	D2D1_BITMAP_PROPERTIES1 props = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
	HRESULT hr;
	hr = m_context->CreateBitmapFromDxgiSurface(target, &props, &targetBitmap);
	if(FAILED(hr)) {
		throw hr;
	}
	m_context->SetTarget(targetBitmap);
}

CComPtr<ID2D1SolidColorBrush> Lib2DDeviceContext::GetSolidColorBrush( D2D1::ColorF color )
{
	D2D1_BRUSH_PROPERTIES props;
	props.opacity = 1.0f;
	props.transform = D2D1::Matrix3x2F::Identity();
	CComPtr<ID2D1SolidColorBrush> retval;
	HRESULT hr;
	hr = m_context->CreateSolidColorBrush(color, props, &retval);
	if(FAILED(hr)) {
		throw hr;
	}
	return retval;
}

void Lib2DDeviceContext::DrawShapes( std::vector<ILib2DShape*> shapes )
{
	m_context->BeginDraw();
	for(std::function<void()> f : preCommands) {
		f();
	}
	for(int i = 0; i<shapes.size(); i++) {
		shapes[i]->draw(m_context);
	}
	m_context->EndDraw();
}

void Lib2DDeviceContext::Clear( D2D1::ColorF color, bool immediate )
{
	if(immediate) {
		m_context->BeginDraw();
		m_context->Clear(color);
		m_context->EndDraw();
	} else {
		const D2D1_COLOR_F* pColor = &color;
		preCommands.push_back([&](){m_context->Clear(color);});
		//decltype((void(ID2D1DeviceContext::*)(const D2D1_COLOR_F&)) &ID2D1DeviceContext::Clear); <void(ID2D1DeviceContext::*)(const D2D1_COLOR_F&)>
	}
}
