#ifndef LIBINPUT_AXIS_H
#define LIBINPUT_AXIS_H
#include <string>
namespace Input {
	class Axis {
	public:
		Axis();
		explicit operator float() const;
		void SetPosition(float newPos);
	private:
		float _pos;
	};
}

#endif
