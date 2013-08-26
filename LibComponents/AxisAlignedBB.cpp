#include "AxisAlignedBB.h"
namespace Components {
	AxisAlignedBB::AxisAlignedBB(const Eigen::AlignedBox3f& bbox)
		: RestAABB(bbox), CurAABB(bbox)
	{

	}
}