#include "stdafx.h"
#include "System.h"

namespace LibCommon {
	System::System(std::set<std::type_index> types) 
		: aspect(types) {

	}
	System::System() {

	}
}