#include "AxisAlignedBBSystem.h"
#include <LibComponents/AxisAlignedBB.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Model.h>
namespace Systems {
	namespace {
		void squareAABB(Eigen::AlignedBox3f* other);
	}
	AxisAlignedBBSystem::AxisAlignedBBSystem()
		: System({ typeid(Components::AxisAlignedBB), typeid(Components::Transform3D) })
	{
		priority = LibCommon::Priority::LOW;
	}
	void AxisAlignedBBSystem::Process(LibCommon::Entity* ent) {
		auto model = ent->GetOptional<Components::Model>();
		auto aabb = ent->Get<Components::AxisAlignedBB>();
		auto transform = ent->Get<Components::Transform3D>();
		if (model && aabb->AABB.volume() == 0) {
			aabb->AABB = calculateBox(*model);
		} else {
			Eigen::Affine3f translationPart(Eigen::Translation3f{transform->transform.translation()});
			aabb->AABB.min() = translationPart * aabb->AABB.min();
			aabb->AABB.max() = translationPart * aabb->AABB.max();
		}
	}
	Eigen::AlignedBox3f AxisAlignedBBSystem::calculateBox(const Components::Model& mod) {
		Eigen::AlignedBox3f rv;
		for (auto& vert : mod.verts) {
			Eigen::Vector3f threePos{vert.pos.x(), vert.pos.y(), vert.pos.z()};
			if (!rv.contains(threePos)) {
				rv.extend(threePos);
			}
		}
		
		squareAABB(&rv);
		return rv;
	}
	
	void squareAABB ( Eigen::AlignedBox3f* other ) {
		if(other->min().x() < other->min().y()) {
			other->min().y() = other->min().x();
		} else {
			other->min().x() = other->min().y();
		}
		if(other->max().x() < other->max().y()) {
			other->max().y() = other->max().x();
		} else {
			other->max().x() = other->max().y();
		}
	}

}