#pragma once
#include "ILib2DShape.h" 

///-------------------------------------------------------------------------------------------------
/// <summary>	A scene stores a collection of shapes (ILib2DShapes) and defines interactions
/// 			between them </summary>
///
/// <remarks>	Charlie, 1/25/2013. </remarks>
///-------------------------------------------------------------------------------------------------
class ILib2DScene : public ILib2DShape {
public:
	///-------------------------------------------------------------------------------------------------
	/// <summary>	Execute before drawing  </summary>
	///
	/// <remarks>	Charlie, 1/25/2013. </remarks>
	///-------------------------------------------------------------------------------------------------
	virtual void PreDraw() = 0;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Execute after drawing </summary>
	///
	/// <remarks>	Charlie, 1/25/2013. </remarks>
	///-------------------------------------------------------------------------------------------------

	virtual void PostDraw() =0;
	virtual ~ILib2DScene() = 0;
};