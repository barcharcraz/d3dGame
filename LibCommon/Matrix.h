#ifndef H_LIBCOMMON_MATRIX
#define H_LIBCOMMON_MATRIX

namespace LibCommon {
	struct Matrix22 {
		float _11; float _21;
		float _12; float _22;
	};

	struct Matrix33 {
		float _11; float _21; float _31;
		float _12; float _22; float _32;
		float _13; float _23; float _33;
	};
	
	struct Matrix44 {
		float _11; float _21; float _31; float _41;
		float _12; float _22; float _32; float _42;
		float _13; float _23; float _33; float _43;
		float _14; float _24; float _34; float _44;
	};
}

#endif