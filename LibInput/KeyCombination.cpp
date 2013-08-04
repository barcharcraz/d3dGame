#include "stdafx.h"
#include "KeyCombination.h"
namespace Input {
	KeyCombination::KeyCombination(std::initializer_list<Keys> combo) {
		_combo.fill(false);
		for (auto key : combo) {
			_combo[key] = true;
		}
	}
	KeyCombination::KeyCombination(Keys key) {
		_combo.fill(false);
		_combo[key] = true;
	}
	KeyCombination::KeyCombination() {
		_combo.fill(false);
	}
	void KeyCombination::Clear() {
		_combo.fill(false);
	}
	void KeyCombination::Clear(Keys key) {
		_combo[key] = false;
	}
	void KeyCombination::Set(Keys key) {
		_combo[key] = true;
	}
	bool KeyCombination::Get(Keys key) {
		return _combo[key];
	}
	bool KeyCombination::Match(const KeyCombination& other) const {
		for (unsigned int i = 0; i < other._combo.size(); ++i) {
			if (other._combo[i]) {
				if (!_combo[i]) {
					return false;
				}
			}
		}
		return true;
	}
}