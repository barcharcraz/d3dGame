#include "stdafx.h"
#include "GLModelRenderer.h"
#include "GLShader.h"
#include "GLUniforms.h"
#include "GLUtils.h"
#include <set>
#include <iostream>
#include <system_error>
#include <algorithm>
#include <Eigen/Geometry>
#include <Eigen/Core>
#include <LibComponents/Model.h>
#include <LibComponents/Camera.h>
#include <LibComponents/Texture.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Velocity.h>
#include <LibComponents/PointLight.h>
#include <LibComponents/DirectionalLight.h>
#include <LibComponents/Material.h>
#include <LibCommon/Scene.h>
#include <LibCommon/Data.h>
namespace LibOpenGL {
    

    GLModelRenderer::GLModelRenderer( OpenGLRenderer* render_arg )
        : System({typeid(Components::Model), 
		typeid(Components::Transform3D), 
		typeid(Components::Effect), 
		typeid(Components::Texture),
		typeid(Components::Material)}),
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
		auto mat = ent->Get<Components::Material>();
        _transforms.model = transform->transform.matrix();
        auto& buffer = updateBuffers(ent);
        auto& program = program_map.at(effect);
        auto& tex = tex_map.at(ent);
        CheckError();
        if(render->ActiveProgram != program.ProgramID()) {
            render->ActiveProgram = program.ProgramID();
            gl::UseProgram(render->ActiveProgram);
        }
        
        tex.Bind();
        bindUniforms(render->ActiveProgram);
        bindModel(render->ActiveProgram);
		BindMaterial(render->ActiveProgram, "mat", *mat);
        bindDirLights(render->ActiveProgram, effect->defines["NUM_DIRECTIONAL"]);
        bindPointLights(render->ActiveProgram, effect->defines["NUM_POINT"]);
        gl::BindVertexArray(buffer.vao.name());
        gl::EnableVertexAttribArray(0);
        gl::EnableVertexAttribArray(1);
        gl::EnableVertexAttribArray(2);
        GLint posLoc = gl::GetAttribLocation(render->ActiveProgram, "pos");
        GLint normLoc = gl::GetAttribLocation(render->ActiveProgram, "norm");
        GLint uvLoc = gl::GetAttribLocation(render->ActiveProgram, "uv");
        
        gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffer.Index.GetBuffer());
        gl::BindBuffer(gl::ARRAY_BUFFER, buffer.Vertex.GetBuffer());
        gl::VertexAttribPointer(posLoc, 4, gl::FLOAT, gl::FALSE_, sizeof(LibCommon::Vertex), 0);
        gl::VertexAttribPointer(normLoc, 4, gl::FLOAT, gl::FALSE_, sizeof(LibCommon::Vertex), 0);
        gl::VertexAttribPointer(uvLoc, 4, gl::FLOAT, gl::FALSE_, sizeof(LibCommon::Vertex), 0);
        gl::DrawElements(gl::TRIANGLES, static_cast<GLsizei>(mod->indices.size()), gl::UNSIGNED_INT, 0);
        CheckError(); 
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
    void GLModelRenderer::bindPointLights(GLuint program, int numLights) {
        auto lights = parent->SelectEntities({ typeid(Components::PointLight), typeid(Components::Transform3D) });
        if (lights.empty()) {
            return;
        }
        auto lightStructs = LibCommon::fuse_point_lights(lights);
        //treat numlights as a max
        auto realNumLights = std::min<int>(numLights, lightStructs.size());
        GLuint plightsidx = gl::GetUniformBlockIndex(program, "pointLightBlock");
        CheckError();
        if (plightsidx == gl::INVALID_INDEX) {
            std::cerr << "WARNING: glGetUniformBlockIndex returned INVALID_INDEX for point lights" << std::endl;
        }
        gl::BindBuffer(gl::UNIFORM_BUFFER, dlights.GetBuffer());
        plights.UpdateData(gl::UNIFORM_BUFFER, sizeof(LibCommon::point_light) * realNumLights, 
            &lightStructs[0], gl::DYNAMIC_DRAW);
        gl::BindBufferBase(gl::UNIFORM_BUFFER, plightsidx, plights.GetBuffer());
        gl::UniformBlockBinding(program, plightsidx, 1);
        
        CheckError();
    }
    void GLModelRenderer::bindDirLights(GLuint program, int numLights) {
        auto lights = parent->SelectEntities({ typeid(Components::DirectionalLight) });
        if (lights.empty()) {
            return;
        }
        auto lightStructs = LibCommon::fuse_dir_lights(lights);
		Eigen::Matrix4f mvtrans = _transforms.view;
		mvtrans.col(3) = Eigen::Vector4f{ 0, 0, 0, 1 };
		for (auto& elm : lightStructs) {
			elm.direction = mvtrans * elm.direction;
			
			elm.direction.normalize();
			elm.direction.w() = 1;
		}
        GLuint dlightidx = gl::GetUniformBlockIndex(program, "dirLightBlock");
		lightStructs.resize(numLights, { Eigen::Vector4f::Zero(), Eigen::Vector4f::Zero(), Eigen::Vector4f::Zero() });
        if (dlightidx == gl::INVALID_INDEX) {
            std::cerr <<
                "WARNING: glGetUniformBlockIndex returned "
                "INVALID_INDEX for directional lights" << std::endl;
        }
        int size = 0;
		int structSize = sizeof(LibCommon::directional_light) * numLights;
        gl::GetActiveUniformBlockiv(program, dlightidx, 
                        gl::UNIFORM_BLOCK_DATA_SIZE, &size);
        gl::BindBuffer(gl::UNIFORM_BUFFER, dlights.GetBuffer());
        dlights.UpdateData(gl::UNIFORM_BUFFER, sizeof(LibCommon::directional_light) * numLights, &lightStructs[0], gl::DYNAMIC_DRAW);
        gl::BindBuffer(gl::UNIFORM_BUFFER, 0);
        gl::UniformBlockBinding(program, dlightidx, 0);
        gl::BindBufferRange(gl::UNIFORM_BUFFER, 0, dlights.GetBuffer(), 0, size);
        
    }
    void GLModelRenderer::OnEntityAdd(LibCommon::Entity* ent) {
        auto entEffect = ent->Get<Components::Effect>();
        auto texture = ent->Get<Components::Texture>();
        program_map.emplace(entEffect, GLProgram{ *entEffect });
        tex_map.emplace(ent, GLTexture{ &texture->data() });
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
        auto texIter = tex_map.find(ent);
        if (texIter != tex_map.end()) {
            tex_map.erase(texIter);
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
		Eigen::Affine3f mvtrans(_transforms.model * _transforms.view);
		Eigen::Matrix3f invTrans = mvtrans.linear().inverse().transpose();
        gl::UniformMatrix4fv(viewidx, 1, false, _transforms.view.data());
        gl::UniformMatrix4fv(projidx, 1, false, _transforms.proj.data());
        gl::UniformMatrix3fv(invTransIdx, 1, false, invTrans.data());
        CheckError();
    }
    void GLModelRenderer::bindModel ( GLuint program ) {
        GLuint modelidx = gl::GetUniformLocation(program, "mvp.model");
        gl::UniformMatrix4fv(modelidx, 1, false, _transforms.model.data());
        CheckError();
    }


}
