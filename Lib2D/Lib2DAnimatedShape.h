#pragma once
#include "ILib2DAnimation.h"
#include "ILib2DShape.h"
#include "Lib2DShape.h"
#include "ILib2DTransformableShape.h"
#include <memory>
class Lib2DAnimatedShape : public ILib2DShape {
public:
    Lib2DAnimatedShape(ILib2DAnimation *animation, ILib2DTransformableShape *shape);
    virtual void draw(ID2D1DeviceContext* pContext) override;
    void update(double dt);
private:
    double m_time;
    double m_start;
    const D2D1::Matrix3x2F m_initial;
    ILib2DAnimation* m_animation;
    ILib2DTransformableShape* m_shape;
};