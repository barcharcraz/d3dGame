#include "ModelRenderer.h"
#include <LibComponents/Model.h>
#include <LibComponents/Camera.h>
#include <LibComponents/Texture.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Velocity.h>
namespace LibOpenGL {
    ModelRenderer::ModelRenderer()
        : System({typeid(Components::Model), typeid(Components::Transform3D)})
    {
		
    }
	void ModelRenderer::Process(LibCommon::Entity *ent) {
		using namespace Components;
		auto& mod = ent->Get<Components::Model>();
		
	}
}