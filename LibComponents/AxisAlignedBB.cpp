#include "AxisAlignedBB.h"
namespace Components {
    sparse::ecs::ComponentInfo AxisAlignedBB::stype = sparse::ecs::GenDefCompInfo<AxisAlignedBB>();
	AxisAlignedBB::AxisAlignedBB(const Eigen::AlignedBox3f& bbox)
		: RestAABB(bbox), CurAABB(bbox)
	{
        info = &AxisAlignedBB::stype;
	}
}
