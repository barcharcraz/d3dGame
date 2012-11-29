#pragma once
#include "ILib2DAnimation.h"
#include <d2d1_1.h>
class Lib2DLinearAnimation : public ILib2DAnimation {
public:
    Lib2DLinearAnimation(D2D1::Matrix3x2F end, double time);
    Lib2DLinearAnimation(double x, double y, double time);
    virtual D2D1::Matrix3x2F getTransform(double deltat) override;
private:
    D2D1::Matrix3x2F m_endTransform;
    double length;
};