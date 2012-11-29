#include "stdafx.h"
#include "Lib2DSolidBrush.h"
#include <d2d1_1.h>

Lib2DSolidBrush::Lib2DSolidBrush(D2D1::ColorF color, ID2D1DeviceContext &context) {
    context.CreateSolidColorBrush(color, &m_brush);
}
CComPtr<ID2D1Brush> Lib2DSolidBrush::getBrush() const {
    return m_brush;
}