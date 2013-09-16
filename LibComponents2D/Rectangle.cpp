#include "stdafx.h"
#include "Rectangle.h"

namespace Components {
	Rectangle::Rectangle(const Eigen::Vector2f& bottom_left_arg, const Eigen::Vector2f& top_right_arg )
		: bottom_left(bottom_left_arg), top_right(top_right_arg)
	{

	}
}