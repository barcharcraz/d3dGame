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
		auto& buffer = updateBuffers(ent, mod);
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
		gl::EnableVertexAttribArray(0);
		gl::BindVertexArray(buffer.vao.name());
		
		
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffer.Index.GetBuffer());
		gl::BindBuffer(gl::ARRAY_BUFFER, buffer.Vertex.GetBuffer());
		gl::VertexAttribPointer(0, 4, gl::FLOAT, gl::FALSE_, 0, 0);
		
		gl::DrawElements(gl::TRIANGLES, mod->indices.size(), gl::UNSIGNED_INT, &mod->indices[0]);
		gl::BindVertexArray(0);
	}
	GLModelRenderer::buffers& GLModelRenderer::updateBuffers(LibCommon::Entity* ent, Components::Model *mod) {
		auto bufferItr = buffer_map.find(ent);
		if(bufferItr == buffer_map.end()) {
			bufferItr = buffer_map.emplace(ent, buffers{}).first;
			size_t vert_size = sizeof(LibCommon::Vertex) * mod->verts.size();
			size_t index_size = sizeof(unsigned int) * mod->indices.size();
			bufferItr->second.Vertex.UpdateData(gl::ARRAY_BUFFER, vert_size, &mod->verts[0], gl::DYNAMIC_DRAW);

			bufferItr->second.Index.UpdateData(gl::ELEMENT_ARRAY_BUFFER, index_size, &mod->indices[0], gl::DYNAMIC_DRAW);
		}
		return bufferItr->second;
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
