#include "Transform.h"
namespace Components {
	sparse::ecs::ComponentInfo Transform3D::sinfo = sparse::ecs::GenDefCompInfo<Transform3D>();
	Transform3D::Transform3D(const Eigen::Affine3f& trans)
		: transform(trans)
	{
		info = &Transform3D::sinfo;
	}

}