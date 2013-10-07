#include "stdafx.h"
#include "Axis.h"
#include <Utils/math.h>
#include <cmath>
namespace Input {
	Axis::Axis()
		: _pos(0)
	{

	}
	Axis::operator float() const {
		return _pos;
	}
	void Axis::SetPosition(float newPos) {
		_pos = newPos;
	}
}
