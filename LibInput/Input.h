#ifndef LIBINPUT_INPUT_H
#define LIBINPUT_INPUT_H
#include <array>
#include <unordered_map>
#include <map>
#include <LibComponents/IComponent.h>
#include "Keys.h"
#include "DeviceTypes.h"
#include "KeyCombination.h"
namespace Input {
	class Input : public Components::IComponent {
	public:
		Input();
		void AddAction(const std::string& name, const KeyCombination& action);
		void AddAxisAction(const std::string& name, DeviceType type, AxisName axis);
		void ActivateKey(Keys key);
		void DeactivateKey(Keys key);
		DeviceData* Device(DeviceType type);
		float AxisAction(const std::string& action);
		bool Action(const std::string& action);
	private:
		KeyCombination _pressed;
		std::unordered_map<DeviceType, DeviceData> _devices;
		std::unordered_map<std::string, const Axis&> _axisActions;
		std::unordered_map<std::string, KeyCombination> _actions;
	};
}

#endif