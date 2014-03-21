#include "ParentingSystem.h"
#include <LibComponents/Transform.h>
#include <LibComponents/ParentLink.h>
namespace Systems {
    ParentingSystem::ParentingSystem()
      : System({typeid(Components::ParentLink)})
    {
        
    }
    void ParentingSystem::PreProcess() {
        m_updated.clear();
    }
    void ParentingSystem::Process ( LibCommon::Entity* ent ) {
        traverseLinks(ent->Get<Components::ParentLink>());
    }
    void ParentingSystem::traverseLinks ( Components::ParentLink* link ) {
        if(m_updated.count(link) == 0) {
            link->rotation = link->transform_src->rotation;
            link->position = link->transform_src->position;
            if(link->parent != nullptr) {
                traverseLinks(link->parent);
                if(link->type & Components::ParentLink::ROTATION) {
                    link->rotation = link->parent->rotation * link->transform_src->rotation;
                }
                if(link ->type & Components::ParentLink::TRANSLATION) {
                    link->position = link->parent->position + link->transform_src->position;
                }
            }
            m_updated.insert(link);
        }
    }



}