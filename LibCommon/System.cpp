#include "stdafx.h"
#include "System.h"
#include "Scene.h"
#include <set>
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
	void System::EnableUpdate() {
		parent->SetSystemEvents(this, aspect);
	}
	void System::EnableUpdate(const std::set<std::type_index>& types) {
		parent->SetSystemEvents(this, types);
	}
	void System::SetUpdateFilter(const std::set<std::type_index>& types) {
		parent->SetSystemEvents(this, types);
	}
	void System::NotifyUpdate(Entity* e, Components::IComponent* c) {
		parent->FireUpdateEvent(e, c);
	}
}