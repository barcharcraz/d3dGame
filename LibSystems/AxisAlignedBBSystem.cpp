#include "AxisAlignedBBSystem.h"
#include <LibComponents/AxisAlignedBB.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Model.h>
#include <vector>
#include <limits>
namespace Systems {
	using namespace sparse::ecs;
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
	{
		write_comp = Components::AxisAlignedBB::stype.type;
		update_func = AxisAlignedBBSystem::AABBUpdate;
		state_comp = -1;
	}
	void AxisAlignedBBSystem::AABBUpdate(Row*, const Scene* scene, Row* row) {
		using namespace Components;
		auto models = MakeAdapter<Model>(*scene->GetRow(Model::sinfo.type));
		auto transforms = MakeAdapter<Transform3D>(*scene->GetRow(Transform3D::sinfo.type));
		auto aabbs = MakeAdapter<AxisAlignedBB>(*scene->GetRow(AxisAlignedBB::stype.type));
		auto output = MakeAdapter<AxisAlignedBB>(*row);
		for (auto& elm : aabbs) {
			Eigen::AlignedBox3f newAABB;
			if (models.is_alive(elm.ent) && elm.RestAABB.isNull()) {
				newAABB = calculateBox(models[elm.ent]);
				output[elm.ent].RestAABB = newAABB;
			} else {
				newAABB = elm.RestAABB;
			}
			output[elm.ent].CurAABB = transformAABB(newAABB, transforms[elm.ent].transform);
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
		return rv;
	}
	
	

}