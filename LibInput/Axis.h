#ifndef LIBINPUT_AXIS_H
#define LIBINPUT_AXIS_H
#include <string>
namespace Input {
	class Axis {
		Axis(const std::string& name);
		explicit operator float();
	private:
		long _ceil;
		float _deadzone;
		long _pos;
		std::string _name;
	};
}

#endif