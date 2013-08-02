#include "stdafx.h"
#include "Keys.h"
namespace windows {
	static bool hasInitialized = false;
	static void initKeymap();
	std::map<int, Input::Keys>& getKeymap() {
		if(!hasInitialized) {
			initKeymap();
		}
		return windows_keymap;
	}
	static void initKeymap() {
		windows_keymap[0x41] = Input::A;
		windows_keymap[0x42] = Input::B;
		windows_keymap[0x43] = Input::C;
		windows_keymap[0x44] = Input::D;
		windows_keymap[0x45] = Input::E;
		windows_keymap[0x46] = Input::F;
		windows_keymap[0x47] = Input::G;
		windows_keymap[0x48] = Input::H;
		windows_keymap[0x49] = Input::I;
		windows_keymap[0x4A] = Input::J;
		windows_keymap[0x4B] = Input::K;
		windows_keymap[0x4C] = Input::L;
		windows_keymap[0x4D] = Input::M;
		windows_keymap[0x4E] = Input::N;
		windows_keymap[0x4F] = Input::O;
		windows_keymap[0x50] = Input::P;
		windows_keymap[0x51] = Input::Q;
		windows_keymap[0x52] = Input::R;
		windows_keymap[0x53] = Input::S;
		windows_keymap[0x54] = Input::T;
		windows_keymap[0x55] = Input::U;
		windows_keymap[0x56] = Input::V;
		windows_keymap[0x57] = Input::W;
		windows_keymap[0x58] = Input::X;
		windows_keymap[0x59] = Input::Y;
		windows_keymap[0x5A] = Input::Z;
		windows_keymap[0x30] = Input::Num0;
		windows_keymap[0x31] = Input::Num1;
		windows_keymap[0x32] = Input::Num2;
		windows_keymap[0x33] = Input::Num3;
		windows_keymap[0x34] = Input::Num4;
		windows_keymap[0x35] = Input::Num5;
		windows_keymap[0x36] = Input::Num6;
		windows_keymap[0x37] = Input::Num7;
		windows_keymap[0x38] = Input::Num8;
		windows_keymap[0x39] = Input::Num9;
		windows_keymap[VK_NUMPAD0] = Input::Numpad0;
		windows_keymap[VK_NUMPAD1] = Input::Numpad1;
		windows_keymap[VK_NUMPAD2] = Input::Numpad2;
		windows_keymap[VK_NUMPAD3] = Input::Numpad3;
		windows_keymap[VK_NUMPAD4] = Input::Numpad4;
		windows_keymap[VK_NUMPAD5] = Input::Numpad5;
		windows_keymap[VK_NUMPAD6] = Input::Numpad6;
		windows_keymap[VK_NUMPAD7] = Input::Numpad7;
		windows_keymap[VK_NUMPAD8] = Input::Numpad8;
		windows_keymap[VK_NUMPAD9] = Input::Numpad9;
		windows_keymap[VK_UP] = Input::Up;
		windows_keymap[VK_DOWN] = Input::Down;
		windows_keymap[VK_LEFT] = Input::Left;
		windows_keymap[VK_RIGHT] = Input::Right;

	}
}