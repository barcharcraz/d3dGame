#include "stdafx.h"
#include "Axis.h"
#include <Utils/math.h>
namespace Input {
	Axis::Axis()
		: _ceil(100), _deadzone(0.01f), _pos(0.0f)
	{

	}
	Axis::operator float() const {
		float cval = utils::clamp(_pos, -_ceil, _ceil);
		float ceil = _ceil;
		auto retval = cval / ceil;
		if (abs(retval) < _deadzone) {
			return 0.0f;
		} else {
			return retval;
		}
	}
	void Axis::SetPosition(long newPos) {
		_pos = newPos;
	}
}