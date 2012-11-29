#pragma once
#include "ILib2DBrush.h"
#include <atlbase.h>
class Lib2DSolidBrush : public ILib2DBrush {
public:
    Lib2DSolidBrush(D2D1::ColorF color, ID2D1DeviceContext &context);
    virtual CComPtr<ID2D1Brush> getBrush() const override;
private:
    CComPtr<ID2D1SolidColorBrush> m_brush;
};