#include "GLBillboardRenderer.h"
#include <LibComponents/Billboard.h>
#include <LibComponents/Transform.h>
#include <LibComponents/Effect.h>
#include <LibComponents/Texture.h>
#include <LibCommon/Scene.h>
#include <LibComponents/Camera.h>
#include <LibCommon/Data.h>
#include <LibComponents/Model.h>
#include <LibGLSL/GLSLVertexShader.h>
#include <LibGLSL/GLSLPixelShader.h>
#include "GLUniforms.h"
namespace LibOpenGL {
	using namespace Components;
	using namespace Eigen;
	GLBillboardRenderer::GLBillboardRenderer(OpenGLRenderer* rend)
		: System({ typeid(Components::Billboard), typeid(Components::Transform3D), typeid(Components::Effect) }),
		render(rend)
	{

	}
	void GLBillboardRenderer::PreProcess() {
		auto camera = parent->SelectEntity({ typeid(Components::Camera), typeid(Components::Transform3D) });
		auto viewTrans = camera->Get<Components::Transform3D>();
		trans.view = viewTrans->GenMatrix();
		trans.proj = camera->Get<Camera>()->CameraMatrix;
		trans.view(0, 3) *= -1;
		trans.view(1, 3) *= -1;
		trans.view(2, 3) *= -1;
	}
	void GLBillboardRenderer::Process(LibCommon::Entity* ent) {
		auto model = ent->GetOptional<Model>();
		auto effect = ent->Get<Effect>();
		auto transform = ent->Get<Transform3D>();
		auto texture = ent->GetOptional<Texture>();
		auto& buffer = m_bufmap.at(ent);
		auto& tex = m_texmap.at(ent);
		auto& program = m_progmap.at(ent);
		if (render->ActiveProgram != program.ProgramID()) {
			render->ActiveProgram = program.ProgramID();
			gl::UseProgram(render->ActiveProgram);
		}
		tex.Bind();
		Matrix4f invView = trans.view;
		invView.rightCols<1>() = Vector4f{ 0, 0, 0, 1 };
		invView = invView.transpose().inverse().eval();
		trans.model = transform->GenMatrix() * invView.inverse();
		BindMVP(render->ActiveProgram, trans, "mvp");
		CheckError();
		gl::BindVertexArray(buffer.vao.name());
		gl::EnableVertexAttribArray(0);
		gl::EnableVertexAttribArray(1);
		gl::EnableVertexAttribArray(2);
		CheckError();
		GLint posLoc = gl::GetAttribLocation(render->ActiveProgram, "pos");
		GLint uvloc = gl::GetAttribLocation(render->ActiveProgram, "uv");
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffer.Index.GetBuffer());
		gl::BindBuffer(gl::ARRAY_BUFFER, buffer.Vertex.GetBuffer());
		CheckError();
		gl::VertexAttribPointer(posLoc, 4, gl::FLOAT, gl::FALSE_, sizeof(LibCommon::Vertex), 0);
		gl::VertexAttribPointer(uvloc, 4, gl::FLOAT, gl::FALSE_, sizeof(LibCommon::Vertex), 0);
		CheckError();
		gl::DrawElements(gl::TRIANGLES, static_cast<GLsizei>(model->indices.size()), gl::UNSIGNED_INT, 0);
		CheckError();
	}
	void GLBillboardRenderer::OnEntityAdd(LibCommon::Entity* ent) {
		auto entEffect = ent->Get<Components::Effect>();
		auto texture = ent->Get<Components::Texture>();
		auto mod = ent->Get<Components::Model>();
		m_progmap.emplace(ent, GLProgram{ *entEffect });
		m_texmap.emplace(ent, GLTexture{ &texture->data() });
		size_t vert_size = sizeof(LibCommon::Vertex) * mod->verts.size();
		size_t idx_size = sizeof(unsigned int) * mod->indices.size();
		buffers buf;
		buf.Vertex.UpdateData(gl::ARRAY_BUFFER, vert_size, mod->verts.data(), gl::STATIC_DRAW);
		buf.Index.UpdateData(gl::ELEMENT_ARRAY_BUFFER, idx_size, mod->indices.data(), gl::STATIC_DRAW);
		m_bufmap.emplace(ent, std::move(buf));
	}
	void GLBillboardRenderer::OnEntityRemove(LibCommon::Entity* ent) {
		m_progmap.erase(ent);
		m_texmap.erase(ent);
		m_bufmap.erase(ent);
	}

}