#ifndef LIBCOMPONENTS_TRANSFORM_H
#define LIBCOMPONENTS_TRANSFORM_H
#include "IComponent.h"
#include <Eigen/Geometry>
#include <Utils/event.h>
namespace Components {
	struct Transform3D : public IComponent {
		Transform3D(const Eigen::Affine3f& trans) : transform(trans) {}
		Eigen::Affine3f transform;
	};
	class Transform3DUpdate : public IComponent {};
}
#endif