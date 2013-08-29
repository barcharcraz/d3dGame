
#ifndef LIBOPENGL_MODELRENDERER_H
#define LIBOPENGL_MODELRENDERER_H
#include "stdafx.h"
#include "OpenGLRenderer.h"
#include "GLBuffer.h"
#include "GLProgram.h"
#include "GLAttribArray.h"
#include <Utils/container.h>
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
#include <LibComponents/Effect.h>

namespace LibOpenGL {
    class GLModelRenderer : public LibCommon::System {
    public:
        GLModelRenderer( LibOpenGL::OpenGLRenderer* render_arg );
        virtual void Process(LibCommon::Entity * ent) override;
        virtual void OnEntityRemove(LibCommon::Entity *ent) override;
	private:
		struct buffers {
			GLBuffer Uniform;
			GLBuffer Vertex;
			GLBuffer Index;
			GLAttribArray vao;
		};
		OpenGLRenderer* render;
		utils::map<Components::Effect*, GLProgram> program_map;
		utils::map<LibCommon::Entity*, buffers> buffer_map;
		
    };
}

#endif
