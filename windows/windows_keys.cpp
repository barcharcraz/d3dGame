#include "stdafx.h"
#include "windows_keys.h"
namespace windows {
	static bool hasInitialized = false;
	static void initKeymap();
	std::map<int, LibCommon::Keys>& getKeymap() {
		if(!hasInitialized) {
			initKeymap();
		}
		return windows_keymap;
	}
	static void initKeymap() {
		windows_keymap[0x41] = LibCommon::A;
		windows_keymap[0x42] = LibCommon::B;
		windows_keymap[0x43] = LibCommon::C;
		windows_keymap[0x44] = LibCommon::D;
		windows_keymap[0x45] = LibCommon::E;
		windows_keymap[0x46] = LibCommon::F;
		windows_keymap[0x47] = LibCommon::G;
		windows_keymap[0x48] = LibCommon::H;
		windows_keymap[0x49] = LibCommon::I;
		windows_keymap[0x4A] = LibCommon::J;
		windows_keymap[0x4B] = LibCommon::K;
		windows_keymap[0x4C] = LibCommon::L;
		windows_keymap[0x4D] = LibCommon::M;
		windows_keymap[0x4E] = LibCommon::N;
		windows_keymap[0x4F] = LibCommon::O;
		windows_keymap[0x50] = LibCommon::P;
		windows_keymap[0x51] = LibCommon::Q;
		windows_keymap[0x52] = LibCommon::R;
		windows_keymap[0x53] = LibCommon::S;
		windows_keymap[0x54] = LibCommon::T;
		windows_keymap[0x55] = LibCommon::U;
		windows_keymap[0x56] = LibCommon::V;
		windows_keymap[0x57] = LibCommon::W;
		windows_keymap[0x58] = LibCommon::X;
		windows_keymap[0x59] = LibCommon::Y;
		windows_keymap[0x5A] = LibCommon::Z;
		windows_keymap[0x30] = LibCommon::Num0;
		windows_keymap[0x31] = LibCommon::Num1;
		windows_keymap[0x32] = LibCommon::Num2;
		windows_keymap[0x33] = LibCommon::Num3;
		windows_keymap[0x34] = LibCommon::Num4;
		windows_keymap[0x35] = LibCommon::Num5;
		windows_keymap[0x36] = LibCommon::Num6;
		windows_keymap[0x37] = LibCommon::Num7;
		windows_keymap[0x38] = LibCommon::Num8;
		windows_keymap[0x39] = LibCommon::Num9;
		windows_keymap[VK_NUMPAD0] = LibCommon::Numpad0;
		windows_keymap[VK_NUMPAD1] = LibCommon::Numpad1;
		windows_keymap[VK_NUMPAD2] = LibCommon::Numpad2;
		windows_keymap[VK_NUMPAD3] = LibCommon::Numpad3;
		windows_keymap[VK_NUMPAD4] = LibCommon::Numpad4;
		windows_keymap[VK_NUMPAD5] = LibCommon::Numpad5;
		windows_keymap[VK_NUMPAD6] = LibCommon::Numpad6;
		windows_keymap[VK_NUMPAD7] = LibCommon::Numpad7;
		windows_keymap[VK_NUMPAD8] = LibCommon::Numpad8;
		windows_keymap[VK_NUMPAD9] = LibCommon::Numpad9;
		windows_keymap[VK_UP] = LibCommon::Up;
		windows_keymap[VK_DOWN] = LibCommon::Down;
		windows_keymap[VK_LEFT] = LibCommon::Left;
		windows_keymap[VK_RIGHT] = LibCommon::Right;

	}
}