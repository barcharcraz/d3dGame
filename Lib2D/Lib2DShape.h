#pragma once
#include "ILib2DShape.h"
#include "ILib2DTransformableObject.h"
#include "ILib2DTransformableShape.h"
class Lib2DShape : public ILib2DTransformableShape {
public:
	
#pragma region accessors
	virtual D2D1::Matrix3x2F getTransform() const override;
	virtual void setTransform(const D2D1::Matrix3x2F newTransform) override;
#pragma endregion accessors

	void mulTransform(float x, float y);
private:
	D2D1::Matrix3x2F m_transform;
};