#pragma once
#include <d2d1_1.h>
#include <vector>
#include <atlbase.h>

class Lib2DCollider {
public:
	Lib2DCollider(CComPtr<ID2D1Geometry> box);
	bool CollisionTest( const Lib2DCollider &collider) const;
	bool CollisionTest(CComPtr<ID2D1Geometry> geom) const;
	bool CollisionTest(const Lib2DCollider &collider, const D2D1::Matrix3x2F &transform) const;
	bool CollisionTest(CComPtr<ID2D1Geometry> geom, const D2D1::Matrix3x2F &transform) const;
	static bool CollisionTest(const Lib2DCollider &col1, const Lib2DCollider &col2);
private:
	CComPtr<ID2D1Geometry> m_bbox;
};