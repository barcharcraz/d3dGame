#ifndef LIBCOMMON_GEOMETRYFILE_H
#define LIBCOMMON_GEOMETRYFILE_H
#include "stdafx.h"
namespace LibCommon {
	class VertexFile {
	public:
		virtual std::vector<Eigen::Vector3f> verts() = 0;
	};
	class IndexFile {
	public:
		virtual std::vector<int> indices() = 0;
	};
}
#endif