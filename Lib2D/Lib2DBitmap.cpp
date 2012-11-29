#include "stdafx.h"
#include "Lib2DBitmap.h"
#include <objbase.h>

Lib2DBitmap::Lib2DBitmap(void)
{
    CoInitialize(NULL);
    HRESULT hr;
    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IWICImagingFactory,
        (LPVOID*)&m_wicFactory);
    if(FAILED(hr)) {
        throw hr;
    }
}


Lib2DBitmap::~Lib2DBitmap(void)
{
    m_bitmap.Release();
    m_wicConverter.Release();
    m_wicFactory.Release();
    CoUninitialize();
}

void Lib2DBitmap::LoadBitmapFromFile( string uri )
{
	CComPtr<IWICBitmapDecoder> smpDecoder = NULL;
	CComPtr<IWICBitmapFrameDecode> smpSource = NULL;
	CComPtr<IWICStream> smpStream  = NULL;
	HRESULT hr;
	wstring s;
	s.assign(uri.begin(), uri.end());
	hr = m_wicFactory->CreateDecoderFromFilename(s.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &smpDecoder);
	if(FAILED(hr)) {
		throw hr;
	}
	hr = smpDecoder->GetFrame(0, &smpSource);
	if(FAILED(hr)) {
		throw hr;
	}
	hr = m_wicFactory->CreateFormatConverter(&m_wicConverter);
	if(FAILED(hr)) {
		throw hr;
	}
	hr = m_wicConverter->Initialize(smpSource, 
		GUID_WICPixelFormat32bppPBGRA, 
		WICBitmapDitherTypeNone, 
		NULL, 
		0.f, 
		WICBitmapPaletteTypeMedianCut);
	if(FAILED(hr)) {
		throw hr;
	}
}

void Lib2DBitmap::BindToRenderTarget( ID2D1RenderTarget* rt )
{
    HRESULT hr;
    hr = rt->CreateBitmapFromWicBitmap(m_wicConverter,
        NULL, 
        &m_bitmap);
    if(FAILED(hr)) {
        throw hr;
    }

}

CComPtr<ID2D1Bitmap> Lib2DBitmap::getBitmap() {
    return m_bitmap;
}
