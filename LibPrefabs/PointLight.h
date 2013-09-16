#ifndef LIBPREFABS_POINTLIGHT_H
#define LIBPREFABS_POINTLIGHT_H
#include <LibCommon/Entity.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace Prefabs {
	class PointLight : public LibCommon::Entity {
	public:
		PointLight(const Eigen::Vector3f& pos, const Eigen::Vector4f& color);
	};
}

#endif