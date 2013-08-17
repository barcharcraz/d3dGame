#include "stdafx.h"
#include "Group.h"
#include <algorithm>
#include <Utils/sets.h>
namespace Systems {
	Group::Group(const std::string& name, Priority prio)
		: _name(name), _prio(prio)
	{

	}
	void Group::AddSystem(std::unique_ptr<LibCommon::System> && s) {
		//we want to insert the new system at the end of the set of systems with
		//greater than of equal to the same number of aspects
		//so if the current members have aspects of size |5 5 4 2| we would pick 4 and insert
		//before it, if there are no members we insert at the end
		auto posItr = std::find_if(_members.begin(), _members.end(), [&](const LibCommon::System& s){
			if (s.aspect.size() > aspect.size()) {
				return true;
			}
			return false;
		});
		auto& added = _members.insert(posItr, std::move(s));
		if (!utils::includes(aspect, (*added)->aspect)) {
			aspect = utils::set_union(aspect, (*added)->aspect);
		}
		
	}
	void Group::Init() {
		for (auto& elm : _members) {
			elm->Init();
		}
	}
}