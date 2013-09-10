#include "stdafx.h"
#include "GLModelRenderer.h"
#include "GLShader.h"
#include <set>
#include <LibComponents/Model.h>
#include <LibComponents/Camera.h>
#include <LibComponents/Texture.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Velocity.h>
namespace LibOpenGL {
    GLModelRenderer::GLModelRenderer( OpenGLRenderer* render_arg )
        : System({typeid(Components::Model), typeid(Components::Transform3D), typeid(Components::Effect)}),
			render(render_arg)
		
    {
		
    }
	void GLModelRenderer::Process(LibCommon::Entity *ent) {
		using namespace Components;
		auto mod = ent->Get<Components::Model>();
		auto effect = ent->Get<Components::Effect>();
		auto bufferItr = buffer_map.emplace(ent, buffers{}).first;
		bufferItr->second.Vertex.UpdateData(gl::ARRAY_BUFFER, mod->verts.size(), &mod->verts[0], gl::STATIC_DRAW);
		bufferItr->second.Index.UpdateData(gl::ELEMENT_ARRAY_BUFFER, mod->indices.size(), &mod->indices[0], gl::STATIC_DRAW);
		std::unordered_map<Components::Effect*, GLProgram>::iterator program;
		program = program_map.find(effect);
		if(program == program_map.end()) {
			program = program_map.emplace(effect, GLProgram{GLShader(gl::VERTEX_SHADER, effect->vs.name).ShaderID(),
								GLShader(gl::FRAGMENT_SHADER, effect->ps.name).ShaderID()}).first;
			
			
		}
		if(render->ActiveProgram != program->second.ProgramID()) {
			render->ActiveProgram = program->second.ProgramID();
			gl::UseProgram(render->ActiveProgram);
		}
		bufferItr->second.vao.Bind();
		gl::BindBuffer(gl::ARRAY_BUFFER, bufferItr->second.Vertex.GetBuffer());
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, bufferItr->second.Index.GetBuffer());
		gl::EnableVertexAttribArray(0);
		gl::VertexAttribPointer(0, 4, gl::FLOAT, gl::FALSE_, 0, 0);
		gl::DrawElements(gl::TRIANGLES, mod->verts.size(), gl::UNSIGNED_INT, 0);
		
	}
	void GLModelRenderer::OnEntityRemove(LibCommon::Entity *ent) {
		auto bufferIter = buffer_map.find(ent);
		if(bufferIter != buffer_map.end()) {
			buffer_map.erase(bufferIter);
		}
		auto effect = ent->GetOptional<Components::Effect>();
		if(effect) {
			auto effectItr = program_map.find(effect);
			if(effectItr != program_map.end()) {
				program_map.erase(effectItr);
			}
		}
	}
}
