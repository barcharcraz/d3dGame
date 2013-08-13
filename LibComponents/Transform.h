#ifndef LIBCOMPONENTS_TRANSFORM_H
#define LIBCOMPONENTS_TRANSFORM_H
#include "IComponent.h"
#include <Eigen/Geometry>
namespace Components {
	struct Transform3D : public IComponent {
		Transform3D(const Eigen::Affine3f& trans) : transform(trans) {}
		Eigen::Affine3f transform;
	};
	struct Transform2D : public IComponent {
		Transform2D(const Eigen::Affine2f& trans) : transform(trans) {}
		Eigen::Affine2f transform;
	};
}
#endif