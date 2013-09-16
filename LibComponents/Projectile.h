#ifndef LIBCOMPONENTS_PROJECTILE_H
#define LIBCOMPONENTS_PROJECTILE_H
#include "IComponent.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <chrono>
namespace Components {
	class Projectile : public IComponent {
	public:
		Projectile(float damage_arg = 100.0f, std::chrono::milliseconds time_arg = std::chrono::milliseconds(5000));
		float damage;
		std::chrono::milliseconds time_to_live;
		
	};
}

#endif