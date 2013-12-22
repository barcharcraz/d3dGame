#include "PointLight.h"

namespace Components {
	sparse::ecs::ComponentInfo PointLight::sinfo = sparse::ecs::GenDefCompInfo<PointLight>();
	PointLight::PointLight()
		: PointLight(Eigen::Vector4f::Ones(), Eigen::Vector4f::Ones(), 1)
	{

	}
	PointLight::PointLight(const Eigen::Vector4f& diffuse)
		: PointLight(diffuse, Eigen::Vector4f::Ones(), 1)
	{
		
	}
	PointLight::PointLight(unsigned int radius)
		: PointLight(Eigen::Vector4f::Ones(), Eigen::Vector4f::Ones(), radius)
	{

	}
	PointLight::PointLight(const Eigen::Vector4f& diffuse, unsigned int radius)
		: PointLight(diffuse, Eigen::Vector4f::Zero(), radius)
	{

	}
	PointLight::PointLight(const Eigen::Vector4f& diffuse, const Eigen::Vector4f& specular, unsigned int radius)
		: Diffuse(diffuse), Specular(specular), Radius(radius)
	{
		info = &PointLight::sinfo;
	}
}