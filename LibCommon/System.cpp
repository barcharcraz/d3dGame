#include "stdafx.h"
#include "System.h"

namespace LibCommon {
	System::System(const std::set<std::type_index>& types) 
		: aspect(types), priority(Priority::MEDIUM) {

	}
	System::System()
		: priority(Priority::MEDIUM)
	{

	}
	System::System(const std::set<std::type_index>& types, Priority prio)
		: aspect(types), priority(prio)
	{

	}
	System::System(Priority prio)
		: priority(prio)
	{

	}
}