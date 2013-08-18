#ifndef LIBCOMPONENTS_DIRECTIONALLIGHT_H
#define LIBCOMPONENTS_DIRECTIONALLIGHT_H
#include "IComponent.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace Components {
	class DirectionalLight : public IComponent {
	public:
		DirectionalLight(const Eigen::Vector4f& color);
		Eigen::Vector4f Diffuse;
	};
}

#endif