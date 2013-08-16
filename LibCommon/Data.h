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
	inline bool operator==(const Vertex& lhs, const Vertex& rhs) {
		return (
			lhs.norm == rhs.norm &&
			lhs.pos == rhs.pos &&
			lhs.uv == rhs.uv
			);
	}
	struct Transforms {
		Eigen::Matrix4f model;
		Eigen::Matrix4f view;
		Eigen::Matrix4f proj;
	};
	struct point_light {
		Eigen::Vector4f diffuse;
		Eigen::Vector3f position;
	};
}

#endif