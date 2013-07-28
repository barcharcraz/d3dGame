#ifndef LIBCOMPONENTS_TRANSFORM_H
#define LIBCOMPONENTS_TRANSFORM_H
#include "IComponent.h"
#include <Eigen/Geometry>
namespace Components {
	struct Transform3D : public IComponent {
		Eigen::Affine3f transform;
	};
	struct Transform2D : public IComponent {
		Eigen::Affine2f transform;
	};
}
#endif