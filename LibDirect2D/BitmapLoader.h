#pragma once
#include "stdafx.h"
#include <wincodec.h>
#include <wincodecsdk.h>
#include <d2d1_1.h>
#include <string>
namespace LibDirect2D {
	namespace BitmapLoader {
		HRESULT initialize();
		void unInitialize();
		HRESULT LoadImageFromFile(std::wstring file, IWICFormatConverter **ppBitmap);
		HRESULT ConvertBitmap(const IWICBitmap& from, ID2D1Bitmap& to);
		HRESULT LoadImageFromFile(std::wstring file, ID2D1DeviceContext &ctx, ID2D1Bitmap **ppResult);

		template <typename T>
		void SafeRelease (T *pT) {
			if(pT) {
				pT->Release();
				pT = NULL;
			}
		}

		template <typename T>
		void SafeRelease (T **ppT) {
			SafeRelease(*ppT);
		}
	}
}