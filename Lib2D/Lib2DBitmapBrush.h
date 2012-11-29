#pragma once
#include "ILib2DBrush.h"
#include <atlbase.h>
class Lib2DBitmapBrush : public ILib2DBrush {
public:
    Lib2DBitmapBrush(CComPtr<ID2D1Bitmap> map, CComPtr<ID2D1DeviceContext> context);
    virtual CComPtr<ID2D1Brush> getBrush() const override;
private:
    CComPtr<ID2D1BitmapBrush> m_brush;
};