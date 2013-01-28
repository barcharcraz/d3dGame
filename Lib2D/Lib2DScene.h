#pragma once
#include "ILib2DScene.h"
#include "ILib2DPhysicalObject.h"
#include <vector>
class Lib2DScene : ILib2DScene {
public:
	virtual void PreDraw() override;

	virtual void PostDraw() override;

	virtual void draw( ID2D1DeviceContext* pContext ) override;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Adds a shape. </summary>
	///
	/// <remarks>	Charlie, 1/25/2013. </remarks>
	///
	/// <param name="pShape">	[in] The shape to add to the scene </param>
	///-------------------------------------------------------------------------------------------------
	void addShape(ILib2DShape * const pShape);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes pShape from the list, if pShape happens to be in the list
	/// 			multiple times (which honestly it should not but who knows) then
	/// 			it will only remove the first occurrence of pShape </summary>
	///
	/// <remarks>	Charlie, 1/25/2013. </remarks>
	///
	/// <param name="pShape">	the shape to remove </param>
	///-------------------------------------------------------------------------------------------------
	void removeShape(ILib2DShape *pShape);
	bool checkCollision(const ILib2DPhysicalObject *pObj);
	bool checkCollision(const ILib2DPhysicalObject *pObj, const D2D1::Matrix3x2F &pTransform);
private:
	// TODO: maybe this should be a smart pointer
	// fact is that there is a good chance anything pointed to here will be 
	// alive for the lifetime of the program
	std::vector<ILib2DShape*> m_sceneDef;
	//list of all the physical objects contained in m_sceneDef
	//this should always be a subset of m_sceneDef
	std::vector<ILib2DPhysicalObject*> m_physicalCache;
	
	void removePhysicalObj(ILib2DPhysicalObject *pPhysObj);

};