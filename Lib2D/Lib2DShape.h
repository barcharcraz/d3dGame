#pragma once
#include "ILib2DShape.h"
class Lib2DShape : public ILib2DShape {
public:
	__declspec(property (get=getTransform, put=setTransform)) D2D1::Matrix3x2F Transform;
#pragma region accessors
	virtual D2D1::Matrix3x2F getTransform() const;
	virtual void setTransform(const D2D1::Matrix3x2F newTransform);
#pragma endregion accessors

	void mulTransform(float x, float y);
private:
	D2D1::Matrix3x2F m_transform;
};