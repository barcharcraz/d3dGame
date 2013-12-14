#ifndef LIBCOMMON_SCENE_H
#define LIBCOMMON_SCENE_H
#include "IRenderer.h"
#include "Entity.h"
#include "IMessage.h"
#include "Bubbly.h"
#include "UpdateMessage.h"
#include "System.h"
#include <memory>
#include <vector>
#include <chrono>
#include <functional>
#include <Utils/make_unique.h>
#include <Utils/lazy_container.h>
namespace LibCommon {
    class Scene {
    public:
        Scene();
        void Update();
        void EraseSystemsNow();
        Entity* AddEntity(Entity* e);
        Entity* AddEntity(std::unique_ptr<Entity> && e);
        template<typename T, typename... Args>
        T* AddEntity(Args && ... args) {
            return static_cast<T*>(
                AddEntity(std::make_unique<T>(std::forward<Args>(args)...))
                );
        }
        std::unique_ptr<Entity> RemoveEntity(Entity* e);
        System* AddSystem(std::unique_ptr<System> && s);
        System* AddSystem(System * s);
        template<typename T, typename... Args>
        T* AddSystem(Args&&... args) {
            return static_cast<T*>(
                AddSystem(std::make_unique<T>(std::forward<Args>(args)...)));
        }
        
        std::unique_ptr<System> RemoveSystem(System* s);
        void SetSystemEvents(System* s, const std::set<std::type_index>& types);
        void FireUpdateEvent(Entity* e, Components::IComponent* c);
        
        std::vector<Components::IComponent*> SelectComponents(std::type_index type);
        template<typename T>
        std::vector<T*> SelectComponents() {
            std::vector<T*> retval;
            for (auto& ent : _entities) {
                if (ent->HasComponent(typeid(T))) {
                    retval.push_back(ent->Get<T>());
                }
            }
            return retval;
        }
        std::vector<Entity*> SelectEntities(const std::set<std::type_index>& types);
        //! \brief SelectEntities job is to select entities that have the components
        //! specified in the types parameter, depending on how entities are stored
        //! this may involve a database query
        Entity* SelectEntity(const std::set<std::type_index>& types);
    protected:
    private:
        utils::lazy_container<std::unique_ptr<System>> _systems;
        utils::lazy_container<std::unique_ptr<Entity>> _entities;
        std::multimap<std::type_index, System*> _eventRegistrations;
        //! \brief sends a removal message to all systems for the
        //! entity e
        void sendRemoveMessage(Entity* e);
        void sendAddMessage(Entity* e);
        void removeSystemEvents(System* s);
        void UpdateSystems();
        void PostUpdateSystems();
        
        std::chrono::system_clock _clock;
        std::chrono::system_clock::duration _delta;
        std::chrono::system_clock::time_point _lastUpdate;
        std::chrono::milliseconds _rate;
    };
}
#endif
