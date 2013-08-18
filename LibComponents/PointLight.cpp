#include "PointLight.h"

namespace Components {
	PointLight::PointLight()
		: Diffuse({ 1.0f, 1.0f, 1.0f, 1.0f }), Radius(1)
	{

	}
	PointLight::PointLight(const Eigen::Vector4f& diffuse)
		: Diffuse(diffuse), Radius(1)
	{

	}
	PointLight::PointLight(unsigned int radius)
		: Diffuse({ 1.0f, 1.0f, 1.0f, 1.0f }), Radius(radius)
	{

	}
	PointLight::PointLight(const Eigen::Vector4f& diffuse, unsigned int radius)
		: Diffuse(diffuse), Radius(radius)
	{

	}
}