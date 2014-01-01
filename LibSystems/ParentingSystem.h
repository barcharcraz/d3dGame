#ifndef LIBSYSTEMS_PARENTINGSYSTEM_H
#define LIBSYSTEMS_PARENTINGSYSTEM_H
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
#include <LibComponents/ParentLink.h>
#include <unordered_map>
#include <unordered_set>
#include <Eigen/Core>
namespace Systems {
    class ParentingSystem : public LibCommon::System {
    public:
        ParentingSystem();
        virtual void PreProcess() override;
        virtual void Process ( LibCommon::Entity* ent ) override;
    private:
        void traverseLinks(Components::ParentLink* link);
        //list of nodes that we have already updated, so we
        //can just use their current value instead of recomputing it
        std::unordered_set<Components::ParentLink*> m_updated;
    };
}
#endif
