#pragma once
#include <map>
#include <LibCommon/Keys.h>
namespace windows {
	std::map<int, LibCommon::Keys> windows_keymap;
	std::map<int, LibCommon::Keys>& getKeymap();
}