#include "stdafx.h"
#include "Lib2DLinearAnimation.h"
#include <d2d1_1.h>
Lib2DLinearAnimation::Lib2DLinearAnimation(D2D1::Matrix3x2F trans, double length) : m_endTransform(trans), m_length(length) {}
Lib2DLinearAnimation::Lib2DLinearAnimation(double x, double y, double length) : m_length(length) {
    m_endTransform = D2D1::Matrix3x2F::Translation(x, y);
}

D2D1::Matrix3x2F Lib2DLinearAnimation::getTransform(double dt) {
    D2D1::Matrix3x2F retval = D2D1::Matrix3x2F::Identity();
    double endx = m_endTransform._31;
    double endy = m_endTransform._32;
    retval = D2D1::Matrix3x2F::Translation(endx*dt, endy*dt);
    return retval;
}
