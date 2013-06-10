#include "stdafx.h"
#include "Input.h"
namespace LibCommon {
	bool Input::HandleKeypress(Keys key) {
		if(actions.count(key)) {
			InputMessage msg(actions.at(key));
			send(&msg);
			return true;
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
}