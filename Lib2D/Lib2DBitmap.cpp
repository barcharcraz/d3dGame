#include "stdafx.h"
#include "Lib2DBitmap.h"
#include <wincodec.h>

Lib2DBitmap::Lib2DBitmap(void)
{
}


Lib2DBitmap::~Lib2DBitmap(void)
{
}

void Lib2DBitmap::LoadBitmapFromFile( string uri, UINT width, UINT height )
{
	CComPtr<IWICBitmapDecoder> smpDecoder = NULL;
	CComPtr<IWICBitmapFrameDecode> smpSource = NULL;
	CComPtr<IWICStream> smpStream  = NULL;
	CComPtr<IWICFormatConverter> smpConverter = NULL;
	CComPtr<IWICBitmapScaler> smpScaler = NULL;
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
	hr = m_wicFactory->CreateFormatConverter(&smpConverter);
}
