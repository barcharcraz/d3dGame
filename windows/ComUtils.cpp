#include "stdafx.h"
#include "ComUtils.h"
#include <objbase.h>

namespace windows {
	ComInitialize::ComInitialize() {
		CoInitialize(nullptr);
	}
	ComInitialize::~ComInitialize() {
		CoUninitialize();
	}
}