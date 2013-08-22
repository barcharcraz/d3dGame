#include "AxisAlignedBBSystem.h"
#include <LibComponents/AxisAlignedBB.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Model.h>
namespace Systems {
	AxisAlignedBBSystem::AxisAlignedBBSystem()
		: System({ typeid(Components::AxisAlignedBB), typeid(Components::Transform3D) })
	{
		priority = LibCommon::Priority::LOW;
	}
	void AxisAlignedBBSystem::Process(LibCommon::Entity* ent) {
		auto model = ent->GetOptional<Components::Model>();
		if (model) {

		}
	}
	Eigen::AlignedBox3f AxisAlignedBBSystem::calculateBox(const Components::Model& mod) {
		Eigen::AlignedBox3f rv;
		for (auto& vert : mod.verts) {
			if (!rv.contains(vert.pos)) {
				rv.extend(vert.pos);
			}
		}
		return rv;
	}
}