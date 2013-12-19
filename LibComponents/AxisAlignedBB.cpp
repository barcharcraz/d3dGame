#include "AxisAlignedBB.h"
namespace Components {
    sparse::ecs::ComponentType AxisAlignedBB::stype = sparse::ecs::GenID();
	AxisAlignedBB::AxisAlignedBB(const Eigen::AlignedBox3f& bbox)
		: RestAABB(bbox), CurAABB(bbox)
	{
        this->size = sizeof(AxisAlignedBB);
	}
}
