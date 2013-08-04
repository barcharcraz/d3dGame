#include "stdafx.h"
#include "Axis.h"
#include <Utils/math.h>
namespace Input {
	Axis::Axis(const std::string& name)
		: _ceil(500), _deadzone(0.1f), _pos(0.0f), _name(name)
	{

	}
	Axis::operator float() {
		float cval = utils::clamp(_pos, -_ceil, _ceil);
		float ceil = _ceil;
		return cval / ceil;
	}
}