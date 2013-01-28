#pragma once
#include "Lib2DCollider.h"
class ILib2DPhysicalObject {
	// Access the Collider
	

public:
	__declspec(property(get=getCollider, put=setCollider)) Lib2DCollider Collider;
	virtual const Lib2DCollider &getCollider() const = 0;
	virtual void setCollider(const Lib2DCollider &collider) = 0;
	virtual ~ILib2DPhysicalObject() = 0;
};