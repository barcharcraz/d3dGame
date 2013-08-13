#ifndef LIBPREFABS_DIRECTIONALLIGHT_H
#define LIBPREFABS_DIRECTIONALLIGHT_H
#include "stdafx.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <LibCommon/Entity.h>

namespace Prefabs {
	class DirectionalLight : public LibCommon::Entity {
	public:
		DirectionalLight(const Eigen::Vector4f& color, const Eigen::Vector3f& dir);
	};
}

#endif