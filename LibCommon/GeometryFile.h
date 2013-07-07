#ifndef LIBCOMMON_GEOMETRYFILE_H
#define LIBCOMMON_GEOMETRYFILE_H
#include "stdafx.h"
#include "Data.h"
namespace LibCommon {
	class VertexFile {
	public:
		virtual std::vector<Eigen::Vector4f> points() = 0;
		virtual std::vector<Vertex> verts() = 0;
	};
	class IndexFile {
	public:
		virtual std::vector<int> indices() = 0;
	};
}
#endif