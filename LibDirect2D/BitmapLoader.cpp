#include "BitmapLoader.h"
namespace LibDirect2D {
	/* static persistant state about the status of */
	/* image loading in the program */
	static CComPtr<IWICImagingFactory> pFactory;
	static bool isInitialized = false;

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
	
	HRESULT initialize() {
		HRESULT hr = S_OK;
		if(!isInitialized) {
			hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFactory));
			isInitialized = true;
		}
		return hr;
	}
	void unInitialize() {
		pFactory.Release();
	}
	HRESULT LoadImage(std::wstring file, IWICFormatConverter **image) {
		HRESULT hr = S_OK;
		IWICBitmapDecoder *pDecoder = nullptr;
		IWICBitmapFrameDecode *pSource = nullptr;
		IWICStream *pStream = nullptr;
		IWICFormatConverter *pConverter = nullptr;
		IWICBitmapScaler *pScaler = nullptr;
		hr = pFactory->CreateDecoderFromFilename(file.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
		if(FAILED(hr)) {
			return hr;
		}
		hr = pDecoder->GetFrame(0,&pSource);
		if(FAILED(hr)) {
			return hr;
		}
		hr = pFactory->CreateFormatConverter(&pConverter);
		if(FAILED(hr)) {
			return hr;
		}
		hr = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
		if(FAILED(hr)) {
			return hr;
		}
		image = &pConverter;
		pDecoder->Release();
		pSource->Release();
		pStream->Release();
		pScaler->Release();
		return hr;
		
	}
	
	HRESULT LoadImage(std::wstring file, ID2D1DeviceContext &ctx, ID2D1Bitmap **ppResult) {
		IWICFormatConverter * pconv = nullptr;
		HRESULT hr = S_OK;
		hr = LoadImage(file, &pconv);
		if(FAILED(hr)) {
			return hr;
		}
		hr = ctx.CreateBitmapFromWicBitmap(pconv, ppResult);
		if(FAILED(hr)) {
			return hr;
		}

		pconv->Release();
		return hr;

	}
}