#pragma once
#include "stdafx.h"
#include <d2d1_1.h>
#include <atlbase.h>

class ILib2DBrush {
public:
    virtual CComPtr<ID2D1Brush> getBrush() const = 0;
};