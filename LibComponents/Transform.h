#ifndef LIBCOMPONENTS_TRANSFORM_H
#define LIBCOMPONENTS_TRANSFORM_H
#include <ecs.h>
#include <Eigen/Geometry>
#include <Utils/event.h>
namespace Components {
	struct Transform3D : public sparse::ecs::Component {
		static sparse::ecs::ComponentInfo sinfo;
		Transform3D(const Eigen::Affine3f& trans);
		Eigen::Affine3f transform;
	};
}
#endif