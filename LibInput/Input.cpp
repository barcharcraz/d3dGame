#include "Input.h"
namespace Input {
	Input::Input() {

	}
	void Input::AddAction(const std::string& name, const KeyCombination& action) {
		_actions.emplace(name, action);
	}
	void Input::ActivateKey(Keys key) {
		_pressed.Set(key);
	}
	void Input::DeactivateKey(Keys key) {
		_pressed.Clear(key);
	}
	bool Input::ActionStatus(const std::string& action) {
		return _pressed.Match(_actions.at(action));
	}
}