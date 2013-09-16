#include "stdafx.h"
#include "Circle.h"
namespace Components {
	Circle::Circle(const Eigen::Vector2f& center_arg, float radius_arg)
		: center(center_arg), radius(radius_arg)
	{

	}
	Circle::Circle(float radius_arg)
		: center(Eigen::Vector2f{ 0.0f, 0.0f }), radius(radius_arg)
	{

	}
}