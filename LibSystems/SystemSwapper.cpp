#include "SystemSwapper.h"
#include <LibInput/Input.h>
#include <LibCommon/Scene.h>
namespace Systems {
    SystemSwapper::SystemSwapper(
        std::unique_ptr<LibCommon::System>&& a,
        std::unique_ptr<LibCommon::System>&& b,
        std::string keybind)
        : System({ typeid(Input::Input) }), 
        m_keybind(std::move(keybind)), active(std::move(a)), inactive(std::move(b))
    {

    }
    void SystemSwapper::Init() {
        activeptr = active.get();
        parent->AddSystem(std::move(active));
    }
    void SystemSwapper::Process(LibCommon::Entity* ent) {
        auto inp = ent->Get<Input::Input>();
        if (inp->Action(m_keybind)) {
            active = parent->RemoveSystem(activeptr);
            std::swap(active, inactive);
            activeptr = active.get();
            parent->AddSystem(std::move(active));
        }
    }
}