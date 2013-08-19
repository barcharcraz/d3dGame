
#ifndef LIBOPENGL_MODELRENDERER_H
#define LIBOPENGL_MODELRENDERER_H
#include "stdafx.h"
#include "GLBuffer.h"
#include <map>
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
namespace LibOpenGL {
    class ModelRenderer : public LibCommon::System {
    public:
        ModelRenderer();
        virtual void Process(LibCommon::Entity * ent) override;
        virtual void OnEntityRemove(LibCommon::Entity *ent) override;
	private:
		struct buffers {
			GLBuffer Uniform;
			GLBuffer Vertex;
			GLBuffer Index;
		};
		
		std::map<LibCommon::Entity*, buffers> buffer_map;
		
    };
}

#endif
