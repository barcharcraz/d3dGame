#pragma once
#include "stdafx.h"
#include <memory>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <LibComponents2D/Rectangle.h>
namespace LibDirect2D {
	///-------------------------------------------------------------------------------------------------
	/// <summary>	convert from Eigen's Affine2f to d2dmatrix3x2f 
	/// 			this method allocates new memory and copys the 
	/// 			entries of the Affine2f</summary>
	///
	/// <remarks>	Charlie, 5/1/2013. </remarks>
	///
	/// <param name="in">	[in] the input transform </param>
	///
	/// <returns>	a D2D1_MATRIX_3X2F representing the same transform as the affine2f </returns>
	///-------------------------------------------------------------------------------------------------
	D2D1_MATRIX_3X2_F Affine2f_to_D2D1Matrix3x2f(const Eigen::Affine2f &in);
	D2D1_POINT_2F PointConversion(const Eigen::Vector2f& p);
	D2D1_RECT_F RectConversion(const Components::Rectangle& rect);
}