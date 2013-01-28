#pragma once
#include "ILib2DTransformableObject.h"
#include "ILib2DPhysicalObject.h"
#include "ILib2DScene.h"
class Lib2DMovableObject : 
	public ILib2DPhysicalObject, 
	public ILib2DTransformableObject {

private:
	Lib2DCollider m_collider;
	D2D1::Matrix3x2F m_transform;
	ILib2DScene * m_pscene;
public:
	virtual bool setTransform(D2D1::Matrix3x2F newTransform) override;
	virtual D2D1::Matrix3x2F getTransform() const override;
	virtual const Lib2DCollider &getCollider() const override;
	virtual void setCollider(const Lib2DCollider &collider) override;

};