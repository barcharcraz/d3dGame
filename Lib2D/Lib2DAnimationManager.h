#pragma once
#include "ILib2DAnimation.h"
#include "ILib2DShape.h"
#include "Lib2DShape.h"
#include "ILib2DTransformableShape.h"
#include <memory>
class Lib2DAnimationManager{
public:
    Lib2DAnimationManager(ILib2DAnimation *animation, ILib2DTransformableShape *shape);
    Lib2DAnimationManager(ILib2DAnimation *animation, ILib2DTransformableShape *shape, double start);
	void resetTime(double start);
    void update(double dt);
private:
    double m_time;
    double m_start;
	D2D1::Matrix3x2F m_initialTransform;
    ILib2DAnimation* m_animation;
    ILib2DTransformableShape* m_shape;
};