#ifndef LIBINPUT_DEVICETYPES_H
#define LIBINPUT_DEVICETYPES_H
#include "Axis.h"
#include <map>
namespace Input {
	enum class AxisName {
		X,
		Y
	};
	struct DeviceType {
		short usage_page;
		short usage;
	};
	inline bool operator==(const DeviceType& lhs, const DeviceType& rhs) {
		return
			(lhs.usage_page == rhs.usage_page) &&
			(lhs.usage == rhs.usage);
	}
	struct DeviceData {
		std::map<AxisName, Axis> axes;
	};
	const DeviceType MouseType = { 0x01, 0x02 };
	
}
namespace std {
	template<>
	struct hash<Input::DeviceType> {
	public:
		std::size_t operator()(const Input::DeviceType& other) const {
			auto h1 = std::hash<short>()(other.usage_page);
			auto h2 = std::hash<short>()(other.usage);
			return h1 ^ (h2 << 1);
		}
	};
}
#endif
