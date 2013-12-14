#ifndef LIBSYSTEMS_SYSTEMSWAPPER_H
#define LIBSYSTEMS_SYSTEMSWAPPER_H
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
#include <memory>
namespace Systems {
    class SystemSwapper : public LibCommon::System {
    public:
        SystemSwapper(
            std::unique_ptr<LibCommon::System>&& a,
            std::unique_ptr<LibCommon::System>&& b,
            std::string keybind);
        virtual void Init() override;
        virtual void Process(LibCommon::Entity* ent) override;
    private:
        std::string m_keybind;
        LibCommon::System* activeptr;
        std::unique_ptr<LibCommon::System> active;
        std::unique_ptr<LibCommon::System> inactive;
        
    };
}

#endif