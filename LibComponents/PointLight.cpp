#include "PointLight.h"

namespace Components {
	PointLight::PointLight()
		: Diffuse({ 1.0f, 1.0f, 1.0f, 1.0f }), Specular(Eigen::Vector4f::Ones()), Radius(1)
	{

	}
	PointLight::PointLight(const Eigen::Vector4f& diffuse)
		: Diffuse(diffuse), Specular(Eigen::Vector4f::Ones()), Radius(1)
	{
		
	}
	PointLight::PointLight(const Eigen::Vector4f& diffuse, const Eigen::Vector4f& specular, unsigned int radius)
		: Diffuse(diffuse), Specular(specular), Radius(radius)
	{

	}
	PointLight::PointLight(unsigned int radius)
		: Diffuse({ 1.0f, 1.0f, 1.0f, 1.0f }), Specular(Eigen::Vector4f::Ones()), Radius(radius)
	{

	}
	PointLight::PointLight(const Eigen::Vector4f& diffuse, unsigned int radius)
		: Diffuse(diffuse), Specular(Eigen::Vector4f::Ones()), Radius(radius)
	{

	}
}