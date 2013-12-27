#ifndef LIBOPENGL_GLBILLBOARDRENDERER_H
#define LIBOPENGL_GLBILLBOARDRENDERER_H
#include <LibCommon/System.h>
#include <LibCommon/Data.h>
#include "OpenGLRenderer.h"
#include <unordered_map>
#include "GLProgram.h"
#include "GLTexture.h"
#include "GLBuffer.h"
#include "GLData.h"
namespace LibOpenGL {
	class GLBillboardRenderer : public LibCommon::System {
	public:
		GLBillboardRenderer(LibOpenGL::OpenGLRenderer* render_arg);
		virtual void PreProcess() override;
		virtual void Process(LibCommon::Entity* ent) override;
		virtual void OnEntityAdd(LibCommon::Entity* ent) override;
		virtual void OnEntityRemove(LibCommon::Entity* ent) override;
	private:
		OpenGLRenderer* render;
		LibCommon::Transforms trans;
		std::unordered_map<LibCommon::Entity*, GLProgram> m_progmap;
		std::unordered_map<LibCommon::Entity*, GLTexture> m_texmap;
		std::unordered_map<LibCommon::Entity*, buffers> m_bufmap;
	};
}

#endif