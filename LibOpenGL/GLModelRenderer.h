
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
#include <LibCommon/System.h>
#include <LibCommon/Data.h>
#include <unordered_map>
namespace Components {
	struct Model;
}
namespace LibOpenGL {
    class GLModelRenderer : public LibCommon::System {
    public:
        GLModelRenderer( LibOpenGL::OpenGLRenderer* render_arg );
		virtual void PreProcess() override;
        virtual void Process(LibCommon::Entity * ent) override;
        virtual void OnEntityRemove(LibCommon::Entity *ent) override;
	private:
		struct buffers {
			buffers() = default;
			buffers(const buffers&) = delete;
			buffers(buffers&& other)
				: Uniform(std::move(other.Uniform)),
				Vertex(std::move(other.Vertex)),
				Index(std::move(other.Index)),
				vao(std::move(other.vao)) {}
			GLBuffer Uniform;
			GLBuffer Vertex;
			GLBuffer Index;
			GLAttribArray vao;
		};
		buffers& updateBuffers( LibCommon::Entity* ent );
		void bindUniforms(GLuint program);
		void bindModel(GLuint program);
		OpenGLRenderer* render;
		std::unordered_map<Components::Effect*, GLProgram> program_map;
		std::unordered_map<LibCommon::Entity*, buffers> buffer_map;
		LibCommon::Transforms _transforms;
    };
}

#endif
