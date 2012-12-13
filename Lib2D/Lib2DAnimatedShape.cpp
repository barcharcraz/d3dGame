#include "stdafx.h"
#include "Lib2DAnimatedShape.h"

Lib2DAnimatedShape::Lib2DAnimatedShape(ILib2DAnimation *animation, ILib2DTransformableShape *shape) :
    m_animation(animation), m_shape(shape), m_time(0), m_initial(shape->getTransform()) {
}
void Lib2DAnimatedShape::update(double time) {
    m_time=time;
    m_shape->setTransform(m_shape->getTransform()*m_animation->getTransform(m_time));
}
void Lib2DAnimatedShape::draw(ID2D1DeviceContext* pContext) {
    m_shape->draw(pContext);
}