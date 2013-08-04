#include "Input.h"
namespace Input {
	Input::Input() {

	}
	void Input::AddAction(const std::string& name, const KeyCombination& action) {
		_actions.emplace(name, action);
	}
	void Input::AddAxisAction(const std::string& name, DeviceType type, AxisName axis) {
		_axisActions.emplace(name, _devices[type].axes[axis]);
	}
	void Input::ActivateKey(Keys key) {
		_pressed.Set(key);
	}
	void Input::DeactivateKey(Keys key) {
		_pressed.Clear(key);
	}
	bool Input::Action(const std::string& action) {
		return _pressed.Match(_actions.at(action));
	}
	float Input::AxisAction(const std::string& action) {
		return float(_axisActions.at(action));
	}
	DeviceData* Input::Device(DeviceType type) {
		return &_devices[type];
	}
}