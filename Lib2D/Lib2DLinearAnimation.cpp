#include "stdafx.h"
#include "Lib2DLinearAnimation.h"
#include <d2d1_1.h>
Lib2DLinearAnimation::Lib2DLinearAnimation(D2D1::Matrix3x2F end, double time) : m_endTransform(end), length(time) {}
Lib2DLinearAnimation::Lib2DLinearAnimation(double x, double y, double time) : length(time) {
    m_endTransform = D2D1::Matrix3x2F::Translation(x, y);
}

D2D1::Matrix3x2F Lib2DLinearAnimation::getTransform(double deltat) {
    D2D1::Matrix3x2F retval(m_endTransform);
    retval._11 = (retval._11/length)*deltat;
    retval._12 = (retval._12/length)*deltat;
    retval._21 = (retval._21/length)*deltat;
    retval._22 = (retval._22/length)*deltat;
    retval._31 = (retval._31/length)*deltat;
    retval._32 = (retval._32/length)*deltat;
    return retval;
}