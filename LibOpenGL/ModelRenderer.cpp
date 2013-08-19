#include "stdafx.h"
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
		auto mod = ent->Get<Components::Model>();
		auto& entBuf = buffer_map[ent];
		entBuf.Vertex.UpdateData(mod->verts.size(), &mod->verts[0], gl::VERTEX_ARRAY_BUFFER_BINDING);
	}
	void ModelRenderer::OnEntityRemove(LibCommon::Entity *ent) {
		if(buffer_map.count(ent) != 0) {
			buffer_map.erase(ent);
		}
	}
}
