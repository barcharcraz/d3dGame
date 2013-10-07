#include "stdafx.h"
#include "GLModelRenderer.h"
#include "GLShader.h"
#include <set>
#include <iostream>
#include <system_error>
#include <Eigen/Geometry>
#include <Eigen/Core>
#include <LibComponents/Model.h>
#include <LibComponents/Camera.h>
#include <LibComponents/Texture.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Velocity.h>
#include <LibCommon/Scene.h>
#include <LibCommon/Data.h>
namespace LibOpenGL {
    

    GLModelRenderer::GLModelRenderer( OpenGLRenderer* render_arg )
        : System({typeid(Components::Model), typeid(Components::Transform3D), typeid(Components::Effect)}),
            render(render_arg)
        
    {
        
    }
    void GLModelRenderer::PreProcess () {
        auto cament = parent->SelectEntity({typeid(Components::Camera), typeid(Components::Transform3D)});
        auto cam = cament->Get<Components::Camera>();
        auto camTrans = cament->Get<Components::Transform3D>();
        _transforms.proj = cam->CameraMatrix;
        _transforms.view = camTrans->transform.matrix();
    }

    void GLModelRenderer::Process(LibCommon::Entity *ent) {
        using namespace Components;
        auto mod = ent->Get<Components::Model>();
        auto effect = ent->Get<Components::Effect>();
        auto transform = ent->Get<Components::Transform3D>();
        _transforms.model = transform->transform.matrix();
        auto& buffer = updateBuffers(ent);
        std::unordered_map<Components::Effect*, GLProgram>::iterator program;
        program = program_map.find(effect);
        if(program == program_map.end()) {
            program = program_map.emplace(effect, GLProgram{GLShader(gl::VERTEX_SHADER, effect->vs.name).ShaderID(),
                                GLShader(gl::FRAGMENT_SHADER, effect->ps.name).ShaderID()}).first;
            
            
        }
        CheckError();
        if(render->ActiveProgram != program->second.ProgramID()) {
            render->ActiveProgram = program->second.ProgramID();
            gl::UseProgram(render->ActiveProgram);
            
        }
		bindUniforms(render->ActiveProgram);
        bindModel(render->ActiveProgram);
        gl::BindVertexArray(buffer.vao.name());
        gl::EnableVertexAttribArray(0);
        gl::EnableVertexAttribArray(1);
        //gl::EnableVertexAttribArray(2);
        GLint posLoc = gl::GetAttribLocation(render->ActiveProgram, "pos");
        GLint normLoc = gl::GetAttribLocation(render->ActiveProgram, "norm");
        GLint uvLoc = gl::GetAttribLocation(render->ActiveProgram, "uv");
        
        gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffer.Index.GetBuffer());
        gl::BindBuffer(gl::ARRAY_BUFFER, buffer.Vertex.GetBuffer());
        gl::VertexAttribPointer(posLoc, 4, gl::FLOAT, gl::FALSE_, sizeof(LibCommon::Vertex), 0);
        gl::VertexAttribPointer(normLoc, 4, gl::FLOAT, gl::FALSE_, sizeof(LibCommon::Vertex), 0);
        //gl::VertexAttribPointer(uvLoc, 3, gl::FLOAT, gl::FALSE_, sizeof(LibCommon::Vertex), 0);
        
        gl::DrawElements(gl::TRIANGLES, static_cast<GLsizei>(mod->indices.size()), gl::UNSIGNED_INT, 0);
        
    }
    GLModelRenderer::buffers& GLModelRenderer::updateBuffers(LibCommon::Entity* ent) {
        auto mod = ent->Get<Components::Model>();
        auto bufferItr = buffer_map.find(ent);
        if (bufferItr == buffer_map.end()) {
            bufferItr = buffer_map.emplace(ent, buffers()).first;
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
    void GLModelRenderer::bindUniforms(GLuint program) {
        GLint viewidx = gl::GetUniformLocation(program, "mvp.view");
        GLint projidx = gl::GetUniformLocation(program, "mvp.proj");
		GLint invTransIdx = gl::GetUniformLocation(program, "normTrans");
        CheckError();
        if(projidx == -1) {
            std::cerr << "WARNING: glGetUniformLocation returned -1" << std::endl;
        }
        if(viewidx == -1) {
            std::cerr << "WARNING: glGetUniformLocation returned -1" << std::endl;
        }
		Eigen::Matrix4f invTrans = _transforms.model * _transforms.view;
		invTrans.reverseInPlace();
		invTrans.transposeInPlace();
        gl::UniformMatrix4fv(viewidx, 1, false, _transforms.view.data());
        gl::UniformMatrix4fv(projidx, 1, false, _transforms.proj.data());
		gl::UniformMatrix4fv(invTransIdx, 1, false, invTrans.data());
        CheckError();
    }
    void GLModelRenderer::bindModel ( GLuint program ) {
        GLuint modelidx = gl::GetUniformLocation(program, "mvp.model");
        gl::UniformMatrix4fv(modelidx, 1, false, _transforms.model.data());
        CheckError();
    }


}
