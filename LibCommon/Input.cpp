#include "stdafx.h"
#include "Input.h"
namespace LibCommon {
	Input::Input(const std::map<int, Keys> &kmap)
		: keymap(kmap)
	{
	}

	bool Input::HandleKeypress(Keys key) {
		if(actions.count(key)) {
			InputMessage msg(actions.at(key));
			send(&msg);
			return true;
		} else {
			return false;
		}
	}
	bool Input::HandleKeypress(int systemKeyCode) {
		if(keymap.count(systemKeyCode)) {
			return HandleKeypress(keymap.at(systemKeyCode));
		} else {
			return false;
		}
	}
	bool Input::AddAction(Keys key, std::wstring action) {
		if(actions.count(key)) {
			return false;
		} else {
			actions.emplace(key, action);
			return true;
		}
	}

	bool Input::RemoveAction(std::wstring action) {
		Keys key = Keys::Count;
		if(findAction(action, key))
			return RemoveAction(key);
		else 
			return false;
	}

	bool Input::RemoveAction(Keys key) {
		size_t num = actions.erase(key);
		if(num)
			return true;
		else
			return false;
	}
	bool Input::findAction(std::wstring action, Keys &boundKey) {
		for(std::pair<Keys, std::wstring> p : actions) {
			if(p.second == action) {
				boundKey = p.first;
				return true;
			}
		}
		return false;
	}
}