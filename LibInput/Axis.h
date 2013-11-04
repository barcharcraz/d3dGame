#ifndef LIBINPUT_AXIS_H
#define LIBINPUT_AXIS_H
#include <string>
namespace Input {
	class Axis {
	public:
		Axis();
		explicit operator double() const;
		void SetPosition(double newPos);
	private:
		double _pos;
	};
}

#endif
