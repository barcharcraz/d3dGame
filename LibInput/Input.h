#ifndef LIBINPUT_INPUT_H
#define LIBINPUT_INPUT_H
#include <array>
#include <unordered_map>
#include "Keys.h"
#include "KeyCombination.h"
namespace LibCommon {
	class Input {
	public:
		void AddAction(const std::string& name, const KeyCombination& action);
		void ActivateKey(Keys key);
		void DeactivateKey(Keys key);
	private:
		std::array<bool, Keys::Count> _pressed;
		std::unordered_map<std::string, KeyCombination> _actions;
	};
}

#endif