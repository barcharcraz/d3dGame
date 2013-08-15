#include "PointLight.h"

namespace Components {
	PointLight::PointLight()
		: Color(data.color), Radius(data.radius)
	{
		Color = Eigen::Vector4f{ 1.0f, 1.0f, 1.0f, 1.0f };
		Radius = 1;
	}
	PointLight::PointLight(const Eigen::Vector4f& color)
		: Color(data.color), Radius(data.radius)
	{
		Color = color;
		Radius = 1;
	}
	PointLight::PointLight(unsigned int radius)
		: Color(data.color), Radius(data.radius)
	{
		Color = Eigen::Vector4f{ 1.0f, 1.0f, 1.0f, 1.0f };
		Radius = radius;
	}
	PointLight::PointLight(const Eigen::Vector4f& color, unsigned int radius)
		: Color(data.color), Radius(data.radius)
	{
		Color = color;
		Radius = radius;
	}
}