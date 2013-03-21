#include "Entity.h"
namespace LibCommon {
	void Entity::draw(IUnknown* pContext) {
		for(vector<IComponent>::iterator i = Components.begin(); i != Components.end(); i++) {
			i->Update();
		}
	}
}