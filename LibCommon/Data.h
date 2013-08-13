#ifndef LIBCOMMON_DATA_H
#define LIBCOMMON_DATA_H
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace LibCommon {
	struct Vertex {
		Eigen::Vector4f pos;
		Eigen::Vector4f norm;
		Eigen::Vector3f uv;
	};

	struct Transforms {
		Eigen::Matrix4f model;
		Eigen::Matrix4f view;
		Eigen::Matrix4f proj;
	};
}

#endif