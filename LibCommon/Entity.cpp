#include "stdafx.h"
#include "Entity.h"
#include <algorithm>
#include <Utils/exceptions.h>
namespace LibCommon {
    using namespace Components;
    Entity::Entity() {

    }
    Entity::~Entity() {

    }
    void Entity::AddComponent ( IComponent* c ) {
        using namespace std;
        //typeid(*c) works because type_index has an implicit
        //conversion from type_info
        c->ent = this;
        _components.emplace ( typeid ( *c ), std::unique_ptr<IComponent> ( c ) );
    }
    void Entity::AddComponent ( std::unique_ptr<IComponent> && c ) {
        using namespace std;
        c->ent = this;
        _components.emplace ( typeid ( *c.get() ), std::move ( c ) );
    }
    std::unique_ptr<IComponent> Entity::RemoveComponent ( IComponent* comp ) {
        auto rv = RemoveComponentIfExists ( typeid ( *comp ), comp );
        if ( rv == nullptr ) {
            throw utils::not_found_error ( "the component was not found in this entity" );
        }
        rv->ent = nullptr;
        return rv;
    }
    std::unique_ptr<IComponent> Entity::RemoveComponentIfExists ( std::type_index type, IComponent* comp ) {
        auto range = _components.equal_range ( type );
        for ( auto i = range.first; i != range.second; ++i ) {
            if ( i->second.get() == comp ) {
                std::unique_ptr<IComponent> rv = std::move ( i->second );
                _components.erase ( i );
                rv->ent = nullptr;
                return rv;
            }
        }
        //if we did not find the object we would like to just return a nullptr
        return std::unique_ptr<IComponent> ( nullptr );
    }
    bool Entity::HasComponent ( std::type_index type ) {
        return _components.count ( type ) > 0;
    }
    bool Entity::HasAllComponents ( const std::set<std::type_index>& types ) {
        bool retval = true;
        for ( auto & type : types ) {
            if ( _components.count ( type ) == 0 ) {
                retval = false;
            }
        }

        return retval;
    }

}
