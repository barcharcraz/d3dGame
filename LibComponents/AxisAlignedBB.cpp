#include "AxisAlignedBB.h"
namespace Components {
	AxisAlignedBB::AxisAlignedBB(const Eigen::AlignedBox3f& bbox)
		: AABB(bbox)
	{

	}
	AxisAlignedBB::AxisAlignedBB(Eigen::AlignedBox3f && bbox)
		: AABB(std::move(bbox))
	{

	}
}