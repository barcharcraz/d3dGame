#include "Input.h"
namespace Input {
	void Input::AddAction(const std::string& name, const KeyCombination& action) {
		_actions.emplace(name, action);
	}
}