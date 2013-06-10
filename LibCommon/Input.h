#ifndef LIBCOMMON_INPUT_H
#define LIBCOMMON_INPUT_H
#include "Entity.h"
#include "IComponent.h"
#include "InputMessage.h"
#include <map>
#include <string>
namespace LibCommon {
	class Input : public Entity {
	public:
		//names of keys in no particular order
		enum Keys {
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			Num0,
			Num1,
			Num2,
			Num3,
			Num4,
			Num5,
			Num6,
			Num7,
			Num8,
			Num9,
			Numpad0,
			Numpad1,
			Numpad2,
			Numpad3,
			Numpad4,
			Numpad5,
			Numpad6,
			Numpad7,
			Numpad8,
			Numpad9,
			Up,
			Down,
			Left,
			Right,
			Count
		};
		bool HandleKeypress(Keys key);
		bool AddAction(Keys key, std::wstring action);
	private:
		std::map<Keys, std::wstring> actions;
	};
}
#endif