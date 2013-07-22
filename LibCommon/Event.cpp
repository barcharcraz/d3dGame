#include "Event.h"
namespace LibCommon {
	void Event::disconnect(connection index) {
		for (auto i = componentConnections.begin(); i != componentConnections.end(); ++i) {
			if (i->second == index) {
				componentConnections.erase(i);
			}
		}
		callbacks.erase(index);
	}
	void Event::disconnect(IComponent* component) {
		auto range = componentConnections.equal_range(component);
		for (auto i = range.first; i != range.second; ++i) {
			callbacks.erase(i->second);
		}
		componentConnections.erase(range.first, range.second);
	}
	void Event::send(IMessage * v) {
		auto range = callbacks.equal_range(std::type_index(typeid(v)));
		for (auto i = range.first; i != range.second; ++i) {
			i->second(v);
		}
	}
}