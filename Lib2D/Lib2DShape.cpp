#pragma once
#include "stdafx.h"
#include "Lib2DShape.h"


void Lib2DShape::setTransform( const D2D1::Matrix3x2F newTransform )
{
	m_transform = newTransform;
}

D2D1::Matrix3x2F Lib2DShape::getTransform() const
{
	return m_transform;
}

void Lib2DShape::mulTransform( float x, float y )
{
	using namespace D2D1;
	Transform = Transform * Matrix3x2F::Translation(x, y);
}
