#pragma once
#include <d2d1_1.h>
class ILib2DAnimation {
public:
    virtual D2D1::Matrix3x2F getTransform(double deltat) = 0;
};