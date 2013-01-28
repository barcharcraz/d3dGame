#include "stdafx.h"
#include "Lib2DScene.h"

void Lib2DScene::PreDraw() {
	
}

void Lib2DScene::PostDraw() {
	throw std::exception("The method or operation is not implemented.");
}

void Lib2DScene::draw( ID2D1DeviceContext* pContext ) {
	throw std::exception("The method or operation is not implemented.");
}

void Lib2DScene::addShape( ILib2DShape *pShape ) {
	m_sceneDef.push_back(pShape);
	ILib2DPhysicalObject *pPhysicalObj = dynamic_cast<ILib2DPhysicalObject*>(pShape);
	if(pPhysicalObj != nullptr) {
		m_physicalCache.push_back(pPhysicalObj);
	}
}

void Lib2DScene::removeShape( ILib2DShape *pShape ) {
	for(int i = 0; i<m_sceneDef.size(); ++i) {
		if(m_sceneDef[i] == pShape) {
			m_sceneDef.erase(m_sceneDef.begin()+i);
			// if the shape is actually a physicalObject then we can assume that
			// it was added to the phyiscalCache as well as the shape list and so
			// we need to remove it
			// TODO: make faster by indexing the physicalDef to sceneDef somehow
			ILib2DPhysicalObject *pPhysicalObj = dynamic_cast<ILib2DPhysicalObject*>(pShape);
			if(pPhysicalObj != nullptr) {
				removePhysicalObj(pPhysicalObj);
			}
			break;
		}
	}
	
}

void Lib2DScene::removePhysicalObj( ILib2DPhysicalObject *pPhysObj ) {
	for(int i=0; i<m_physicalCache.size(); ++i) {
		if(m_physicalCache[i] == pPhysObj) {
			m_physicalCache.erase(m_physicalCache.begin()+i);
		}
	}
}

bool Lib2DScene::checkCollision( const ILib2DPhysicalObject *pObj ) {
	bool retval = false;
	for(int i=0; i<m_physicalCache.size(); ++i) {
		// we don't want to check if objects are colliding with themselves
		// after all all objects contain themselves
		if(m_physicalCache[i] != pObj) {
			retval=pObj->Collider.CollisionTest(m_physicalCache[i]->Collider);
		}
	}
	return retval;
}
bool Lib2DScene::checkCollision(const ILib2DPhysicalObject *pObj, const D2D1::Matrix3x2F &pTransform) {

}