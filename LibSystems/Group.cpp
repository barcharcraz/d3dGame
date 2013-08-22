#include "stdafx.h"
#include "Group.h"
#include <algorithm>
#include <Utils/sets.h>
namespace Systems {
	Group::Group(const std::string& name, LibCommon::Priority prio)
		: System(prio), _name(name)
	{

	}
	Group::Group(const std::string& name) 
		: _name(name)
	{

	}
	void Group::AddSystem(std::unique_ptr<LibCommon::System> && s) {
		//we want to insert the new system at the end of the set of systems with
		//greater than of equal to the same number of aspects
		//so if the current members have aspects of size |5 5 4 2| we would pick 4 and insert
		//before it, if there are no members we insert at the end
		auto posItr = std::find_if(_members.begin(), _members.end(), [&](const std::unique_ptr<LibCommon::System>& s){
			if (s->aspect.size() > aspect.size()) {
				return true;
			}
			return false;
		});
		
		auto added = _members.insert(posItr, std::move(s));
		auto ptr = added->get();
		if (!utils::includes(aspect, ptr->aspect)) {
			std::set<std::type_index> intersection;
			//we want the new aspect of the group to be the intersection
			//of the aspects if its members. If the aspects of s and this are
			//disjoint than this' aspects is Ø (the empty set) and we will get
			//all entities
			
			std::set_intersection(aspect.begin(), aspect.end(), 
				ptr->aspect.begin(), ptr->aspect.end(),
				std::inserter(intersection, intersection.begin()));
			aspect = std::move(intersection);
		}
		
	}
	void Group::PreProcess() {
		for (auto& elm : _members) {
			elm->Init();
		}
	}
	void Group::Process(LibCommon::Entity* ent) {
		for (auto& elm : _members) {
			if (ent->HasAllComponents(elm->aspect)) {
				elm->Process(ent);
				return; //we only want to process one element, this is the point
			}
		}
	}
	void Group::OnEntityRemove(LibCommon::Entity* ent) {
		for (auto& elm : _members) {
			if (ent->HasAllComponents(elm->aspect)) {
				elm->OnEntityRemove(ent);
				return; //we only want to send the removal message to one entitiy
			}
		}
	}
}