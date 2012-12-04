#pragma once
#include "ILib2DAnimation.h"
#include "ILib2DShape.h"
#include "Lib2DShape.h"
class Lib2DAnimatedShape : public ILib2DShape {
public:
    Lib2DAnimatedShape(ILib2DAnimation *animation, ILib2DShape *shape);
private:
    ILib2DAnimation* m_animation;
};