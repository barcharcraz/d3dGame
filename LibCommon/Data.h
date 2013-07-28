#ifndef LIBCOMMON_DATA_H
#define LIBCOMMON_DATA_H
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace LibCommon {
	struct Vertex {
		Eigen::Vector4f pos;
		Eigen::Vector4f uv;
	};

	struct Transforms {
		Eigen::Matrix4f worldView;
	};
}

#endif