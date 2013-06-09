#include "stdafx.h"
#include "Conversions.h"
namespace LibDirect2D {
	D2D1_MATRIX_3X2_F Affine2f_to_D2D1Matrix3x2f(const Eigen::Affine2f &in) {
		D2D1_MATRIX_3X2_F retval;
		
		auto const mData = in.matrix();
		retval._11 = in(0,0);
		retval._21 = in(0,1);
		retval._31 = in(0,2);
		retval._12 = in(1,0);
		retval._22 = in(1,1);
		retval._32 = in(1,2);
		return retval;
	}
}