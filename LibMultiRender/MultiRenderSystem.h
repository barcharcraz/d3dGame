#ifndef LIBMULTIRENDER_MULTIRENDERSYSTEM_H
#define LIBMULTIRENDER_MULTIRENDERSYSTEM_H
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
#include <LibDirect3D/Direct3DRenderer.h>
#include <LibDirect3D/ModelRenderer.h>
#include <LibOpenGL/OpenGLRenderer.h>
#include <LibOpenGL/GLModelRenderer.h>
#include <windowing/IWindow.h>
namespace Systems {
    class MultiRenderSystem : public LibCommon::System {
        enum class API { GL, DX };
    public:
        MultiRenderSystem(windowing::IMultiWindow* win);
        virtual void Init() override;
        virtual void Process(LibCommon::Entity* ent) override;
    private:
        std::unique_ptr<LibDirect3D::Direct3DRenderer> dxrend = nullptr;
        std::unique_ptr<LibOpenGL::OpenGLRenderer> glrend = nullptr;
        LibCommon::System* renderSys = nullptr;
        API active = API::DX;
        windowing::IMultiWindow* m_win;
    };
}

#endif