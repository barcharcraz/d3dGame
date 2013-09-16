#include "stdafx.h"
#include "Line.h"

namespace Components {
	Line::Line(const Eigen::Vector2f& a_arg, const Eigen::Vector2f& b_arg) 
		: a(a_arg), b(b_arg)
	{

	}
	Line::Line(const Eigen::Vector2f& b_arg)
		: a(Eigen::Vector2f{ 0.0f, 0.0f }), b(b_arg)
	{

	}
}