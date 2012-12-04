#pragma once
#include <d2d1_1.h>
class ILib2DTransformableObject {
public:
    __declspec(property (get=getTransform, put=setTransform)) D2D1::Matrix3x2F Transform;
    virtual D2D1::Matrix3x2F getTransform() const = 0;
    virtual void setTransform(D2D1::Matrix3x2F newTransform) = 0;
};