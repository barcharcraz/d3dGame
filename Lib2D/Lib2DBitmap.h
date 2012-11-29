#pragma once
#include "lib2dshape.h"
#include <string>
#include <wincodec.h>
#include <atlbase.h>
using namespace std;
class Lib2DBitmap
{
public:
	Lib2DBitmap(void);
	~Lib2DBitmap(void);
	void BindToRenderTarget(ID2D1RenderTarget* rt);
	void LoadBitmapFromFile(string uri);
    CComPtr<ID2D1Bitmap> getBitmap();
private:
	CComPtr<IWICImagingFactory> m_wicFactory;
	CComPtr<IWICFormatConverter> m_wicConverter;
	CComPtr<ID2D1Bitmap> m_bitmap;
};

