
#ifndef LIBOPENGL_MODELRENDERER_H
#define LIBOPENGL_MODELRENDERER_H
#include "stdafx.h"
#include "OpenGLRenderer.h"
#include "GLBuffer.h"
#include "GLProgram.h"
#include "GLTexture.h"
#include "GLAttribArray.h"
#include <Utils/container.h>
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
#include <LibComponents/Effect.h>
#include <LibCommon/System.h>
#include <LibCommon/Data.h>
#include <unordered_map>
#include "GLData.h"
namespace Components {
	struct Model;
}
namespace LibOpenGL {
    class GLModelRenderer : public LibCommon::System {
    public:
        GLModelRenderer( LibOpenGL::OpenGLRenderer* render_arg );
		virtual void PreProcess() override;
        virtual void Process(LibCommon::Entity * ent) override;
		virtual void OnEntityAdd(LibCommon::Entity* ent) override;
        virtual void OnEntityRemove(LibCommon::Entity *ent) override;
	private:
		
		buffers& updateBuffers( LibCommon::Entity* ent );
		void bindUniforms(GLuint program);
		void bindModel(GLuint program);
		void bindTextures(GLuint program);
        void bindDirLights(GLuint program, int numLights);
        void bindPointLights(GLuint program, int numLights);
		OpenGLRenderer* render;
		GLBuffer plights;
		GLBuffer dlights;
		std::unordered_map<Components::Effect*, GLProgram> program_map;
		std::unordered_map<LibCommon::Entity*, buffers> buffer_map;
		std::unordered_map<LibCommon::Entity*, GLTexture> tex_map;
		LibCommon::Transforms _transforms;
    };
}

#endif
