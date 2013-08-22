#include "AxisAlignedBB.h"
namespace Components {
	AxisAlignedBB::AxisAlignedBB(const Eigen::AlignedBox3f& bbox)
		: RestAABB(bbox)
	{

	}
	AxisAlignedBB::AxisAlignedBB(Eigen::AlignedBox3f && bbox)
		: RestAABB(std::move(bbox))
	{

	}
}