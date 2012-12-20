#include "stdafx.h"
#include "Lib2DAnimationManager.h"


/// <summary>
/// Initializes a new instance of the <see cref="Lib2DAnimationManager" /> class. Assumes that the start time of the animation is
/// 0
/// </summary>
/// <param name="animation">The animation.</param>
/// <param name="shape">The shape. this will be modified each time update is called</param>
Lib2DAnimationManager::Lib2DAnimationManager(ILib2DAnimation *animation, ILib2DTransformableShape *shape) :
	m_animation(animation), m_shape(shape), m_time(0) {
		m_initialTransform = m_shape->getTransform();
}
Lib2DAnimationManager::Lib2DAnimationManager(ILib2DAnimation *animation, ILib2DTransformableShape *shape, double start) : 
	m_start(start), m_time(start), m_animation(animation), m_shape(shape) {
		m_initialTransform = m_shape->getTransform();
}

void Lib2DAnimationManager::resetTime(double start) {
	m_start = start;
	m_initialTransform = m_shape->getTransform();
}

void Lib2DAnimationManager::update(double time) {
	m_time=time;
	double dt = m_time - m_start;
	D2D1::Matrix3x2F animTrans = m_animation->getTransform(dt);
	m_shape->setTransform(m_initialTransform * animTrans);
}
