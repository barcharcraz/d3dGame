#include "stdafx.h"
#include "Lib2DCollider.h"

bool Lib2DCollider::CollisionTest(CComPtr<ID2D1Geometry> geom) const {
	return CollisionTest(geom, D2D1::Matrix3x2F::Identity());
}

bool Lib2DCollider::CollisionTest(const Lib2DCollider &collider) const {
	return CollisionTest(collider.m_bbox);
}

bool Lib2DCollider::CollisionTest( const Lib2DCollider &col1, const Lib2DCollider &col2 ) {
	return col1.CollisionTest(col2);
}

bool Lib2DCollider::CollisionTest(const Lib2DCollider &collider, const D2D1::Matrix3x2F &transform) const {
	return CollisionTest(collider.m_bbox, transform);
}

bool Lib2DCollider::CollisionTest(CComPtr<ID2D1Geometry> geom, const D2D1::Matrix3x2F &transform) const {
	D2D1_GEOMETRY_RELATION pRelation;
	m_bbox->CompareWithGeometry(geom, transform, &pRelation);
	//note that we will return true if *pRelation equals D2D1_GEOMETRY_RELATION_UNKNOWN
	//but according to MSDN this is not returned by any D2D function
	if(pRelation == D2D1_GEOMETRY_RELATION_DISJOINT) {
		return false;
	} else {
		return true;
	}
}

