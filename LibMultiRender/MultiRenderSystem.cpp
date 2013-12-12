#include "MultiRenderSystem.h"
#include <LibInput/Input.h>
#include <LibCommon/Scene.h>
namespace Systems {
    MultiRenderSystem::MultiRenderSystem(windowing::IMultiWindow* win)
        : System({ typeid(Input::Input) }), m_win(win)
    {
    }
    void MultiRenderSystem::Init() {
        glrend = std::make_unique<LibOpenGL::OpenGLRenderer>(m_win);
        renderSys = this->parent->AddSystem<LibOpenGL::GLModelRenderer>(glrend.get());

    }
    void MultiRenderSystem::Process(LibCommon::Entity* ent) {
        auto inp = ent->Get<Input::Input>();
        if (inp->Action("SwapAPI")) {
            if (active == API::GL) {
                this->parent->RemoveSystem(renderSys);
                glrend.reset(nullptr);
                dxrend = std::make_unique<LibDirect3D::Direct3DRenderer>(m_win);
                renderSys = parent->AddSystem<LibDirect3D::ModelRenderer>(dxrend.get());
                active = API::DX;
            } else if (active == API::DX) {
                this->parent->RemoveSystem(renderSys);
                dxrend.reset(nullptr);
                glrend = std::make_unique<LibOpenGL::OpenGLRenderer>(m_win);
                renderSys = parent->AddSystem<LibOpenGL::GLModelRenderer>(glrend.get());
                active = API::GL;
            }
        }
    }
}