#pragma once
#include<d2d1_1.h>
#include<d3d11_1.h>
///-------------------------------------------------------------------------------------------------
/// <summary>	Factory for Lib2D resources. </summary>
///
/// <remarks>	Charlie, 10/5/2012. </remarks>
///-------------------------------------------------------------------------------------------------

class Lib2DFactory {
public:
	Lib2DFactory();
	Lib2DFactory(ID3D11Device *device);
	~Lib2DFactory();
};

