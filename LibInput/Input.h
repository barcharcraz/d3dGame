#ifndef LIBINPUT_INPUT_H
#define LIBINPUT_INPUT_H
#include <array>
#include <unordered_map>
#include <LibComponents/IComponent.h>
#include "Keys.h"
#include "KeyCombination.h"
namespace Input {
	class Input : public Components::IComponent {
	public:
		Input();
		void AddAction(const std::string& name, const KeyCombination& action);
		void ActivateKey(Keys key);
		void DeactivateKey(Keys key);
		bool ActionStatus(const std::string& action);
	private:
		KeyCombination _pressed;
		std::unordered_map<std::string, KeyCombination> _actions;
	};
}

#endif