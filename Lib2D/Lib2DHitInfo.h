#include <memory>
#include "ILib2DTransformableObject.h"
#include <d2d1_1.h>
#pragma once
struct HitInfo {
    std::auto_ptr<ILib2DTransformableObject> hit;
    D2D1_VECTOR_2F pos;
};