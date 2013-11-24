#ifndef LIBCOMPONENTS_DIRECTIONALLIGHT_H
#define LIBCOMPONENTS_DIRECTIONALLIGHT_H
#include "IComponent.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace Components {
	class DirectionalLight : public IComponent {
	public:
		DirectionalLight(const Eigen::Vector4f& color, const Eigen::Vector4f& dir_arg);
		DirectionalLight(const Eigen::Vector4f& diffuse_arg, const Eigen::Vector4f& specular_arg, const Eigen::Vector4f& dir_arg);
		Eigen::Vector4f Diffuse;
		Eigen::Vector4f Specular;
		Eigen::Vector4f Direction;
	};
}

#endif