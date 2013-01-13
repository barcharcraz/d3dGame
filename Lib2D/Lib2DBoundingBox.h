#include <atlbase.h>
#include <d2d1_1.h>
#include "Lib2DShape.h"
#include <memory>
#pragma once
struct Lib2DBoundingBox {
    CComPtr<ID2D1Geometry> BoundingBox;
    std::auto_ptr<ILib2DShape> Shape;
};