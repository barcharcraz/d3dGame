#pragma once
#include "stdafx.h"
#include <wincodec.h>
#include <wincodecsdk.h>
#include <atlbase.h>
#include <string>
namespace LibDirect2D {
	HRESULT initialize();
	void unInitialize();
	HRESULT LoadImage(std::wstring file, IWICBitmapSource& ppBitmap);
	HRESULT ConvertBitmap(const IWICBitmap& from, ID2D1Bitmap& to);
	HRESULT LoadImage(std::wstring file, const ID2D1DeviceContext &ctx, ID2D1Bitmap **ppResult);
}