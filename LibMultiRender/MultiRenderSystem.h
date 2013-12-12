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
    public:
        MultiRenderSystem(windowing::IMultiWindow* win);
    private:
        std::unique_ptr<LibDirect3D::Direct3DRenderer> dxrend = nullptr;
        std::unique_ptr<LibOpenGL::OpenGLRenderer> glrend = nullptr;
    };
}

#endif