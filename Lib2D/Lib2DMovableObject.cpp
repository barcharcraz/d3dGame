#include "stdafx.h"
#include "Lib2DMovableObject.h"


bool Lib2DMovableObject::setTransform( D2D1::Matrix3x2F newTransform ) {
	
	m_transform = newTransform;
}

D2D1::Matrix3x2F Lib2DMovableObject::getTransform() const  {
	return m_transform;
}

const Lib2DCollider & Lib2DMovableObject::getCollider() const  {
	return m_collider;
}

void Lib2DMovableObject::setCollider( const Lib2DCollider &collider ) {
	m_collider = collider;
}



