#include "stdafx.h"
#include "Axis.h"
#include <Utils/math.h>
#include <cmath>
namespace Input {
	Axis::Axis()
		: _pos(0)
	{

	}
	Axis::operator double() const {
		return _pos;
	}
	void Axis::SetPosition(double newPos) {
		_pos = newPos;
	}
}
