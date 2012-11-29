#include "stdafx.h"
#include "Lib2DBitmapBrush.h"

Lib2DBitmapBrush::Lib2DBitmapBrush(CComPtr<ID2D1Bitmap> map, CComPtr<ID2D1DeviceContext> context) {
    HRESULT hr;
    hr = context->CreateBitmapBrush(map, &m_brush);
    if(FAILED(hr)) {
        throw hr;
    }
}

CComPtr<ID2D1Brush> Lib2DBitmapBrush::getBrush() const {
    return m_brush;
}