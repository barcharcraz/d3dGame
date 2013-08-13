#include "stdafx.h"
#include "Axis.h"
#include <Utils/math.h>
#include <cmath>
namespace Input {
	Axis::Axis()
		: _ceil(100), _deadzone(0.00f), _pos(0)
	{

	}
	Axis::operator float() const {
		float cval = float(utils::clamp(_pos, -_ceil, _ceil));
		float ceil = float(_ceil);
		auto retval = cval / ceil;
		return retval;
	}
	void Axis::SetPosition(long newPos) {
		_pos = newPos;
	}
}