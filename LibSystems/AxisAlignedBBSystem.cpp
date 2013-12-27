#include "AxisAlignedBBSystem.h"
#include <LibComponents/AxisAlignedBB.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Model.h>
#include <vector>
#include <limits>
namespace Systems {
	namespace {
		Eigen::AlignedBox3f transformAABB(const Eigen::AlignedBox3f& lhs, const Eigen::Affine3f& trans) {
			std::vector<Eigen::Vector3f> transformedPoints;
			for (int i = 0; i < 8; ++i) {
				transformedPoints.push_back(trans * lhs.corner(static_cast<Eigen::AlignedBox3f::CornerType>(i)));
			}
			float minx = std::numeric_limits<float>::max();
			float miny = std::numeric_limits<float>::max();
			float minz = std::numeric_limits<float>::max();
			float maxx = std::numeric_limits<float>::lowest();
			float maxy = std::numeric_limits<float>::lowest();
			float maxz = std::numeric_limits<float>::lowest();
			for (auto& vec : transformedPoints) {
				if (vec.x() < minx) {
					minx = vec.x();
				}
				if (vec.y() < miny) {
					miny = vec.y();
				}
				if (vec.z() < minz) {
					minz = vec.z();
				}
				if (vec.x() > maxx) {
					maxx = vec.x();
				}
				if (vec.y() > maxy) {
					maxy = vec.y();
				}
				if (vec.z() > maxz) {
					maxz = vec.z();
				}
			}
			return Eigen::AlignedBox3f(Eigen::Vector3f{ minx, miny, minz }, Eigen::Vector3f{ maxx, maxy, maxz });
		}
	}
	
	AxisAlignedBBSystem::AxisAlignedBBSystem()
		: System({ typeid(Components::AxisAlignedBB), typeid(Components::Transform3D)})
	{
		priority = LibCommon::Priority::LOW;
		
	}
	void AxisAlignedBBSystem::Init() {
		EnableUpdate({ typeid(Components::Transform3D) });
	}
	void AxisAlignedBBSystem::OnEntityUpdate(LibCommon::Entity* ent, Components::IComponent*) {
		using namespace Eigen;
		auto model = ent->GetOptional<Components::Model>();
		auto aabb = ent->Get<Components::AxisAlignedBB>();
		auto transform = ent->Get<Components::Transform3D>();
		if (model && aabb->RestAABB.isNull()) {
			aabb->RestAABB = calculateBox(*model);
			aabb->CurAABB = aabb->RestAABB;
		}
		Affine3f fullTransform = Translation3f(transform->position.head<3>()) * transform->rotation;
		aabb->CurAABB = transformAABB(aabb->RestAABB, fullTransform);
		NotifyUpdate(ent, aabb);
	}
	Eigen::AlignedBox3f AxisAlignedBBSystem::calculateBox(const Components::Model& mod) {
		Eigen::AlignedBox3f rv;
		for (auto& vert : mod.verts) {
			Eigen::Vector3f threePos{vert.pos.x(), vert.pos.y(), vert.pos.z()};
			if (!rv.contains(threePos)) {
				rv.extend(threePos);
			}
		}
		return rv;
	}
	
	

}