#pragma once
#include "stdafx.h"
#include <wincodec.h>
#include <wincodecsdk.h>
#include <atlbase.h>
#include <string>
namespace LibDirect2D {
	HRESULT LoadImage(std::string file, int width, int height, IWICBitmap& ppBitmap);
	HRESULT ConvertBitmap(const IWICBitmap& from, ID2D1Bitmap& to);
	HRESULT LoadImage(std::string file, int width, int height, ID2D1Bitmap& ppBitmap);
}