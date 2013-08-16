#include <Eigen/Core>
#include <Eigen/Geometry>
#ifndef UTILS_FILES_H
#define UTILS_FILES_H

namespace utils {
	template<typename T>
	inline T clamp(T x, T a, T b) {
		if (x > b)
			return b;
		if (x < a)
			return a;
		return x;
	}
	inline Eigen::Vector3f forwardVector(const Eigen::Affine3f& transform) {
		auto rot = transform.rotation();
		return rot * Eigen::Vector3f::UnitZ();
	}
	inline Eigen::Vector3f upVector(const Eigen::Affine3f& transform) {
		auto rot = transform.rotation();
		return rot * Eigen::Vector3f::UnitY();
	}
	inline Eigen::Vector3f leftVector(const Eigen::Affine3f& transform) {
		auto rot = transform.rotation();
		return rot * Eigen::Vector3f::UnitX();
	}
	
	
}

#endif