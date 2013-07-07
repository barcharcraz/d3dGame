#ifndef LIBCOMMON_DATA_H
#define LIBCOMMON_DATA_H
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace LibCommon {
	struct Vertex {
		Eigen::Vector4f pos;
		Eigen::Vector3f uv;
	};
	struct Model {
		std::vector<Vertex> verts;
		std::vector<int> indices;
	};
}

#endif