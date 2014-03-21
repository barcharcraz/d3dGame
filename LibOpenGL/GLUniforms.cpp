#include "GLUniforms.h"
#include "GLUtils.h"
#include <LibComponents/Material.h>

namespace LibOpenGL {
	void BindTexture(GLuint program, const std::string& name,
		GLuint texture)
	{
		gl::UseProgram(program);
		GLuint baseLoc = gl::GetUniformLocation(program, name.c_str());
		gl::Uniform1ui(baseLoc, 0);
		gl::ActiveTexture(gl::TEXTURE0);
		gl::BindTexture(gl::TEXTURE_2D, texture);
	}
	void BindMaterial(GLuint program, const std::string& name,
		const Components::Material& mat)
	{
		std::string ambiantname = name + ".ambiant";
		std::string diffusename = name + ".diffuse";
		std::string specularname = name + ".specular";
		std::string shinename = name + ".shine";
		GLuint ambiantidx = gl::GetUniformLocation(program, ambiantname.c_str());
		GLuint diffuseidx = gl::GetUniformLocation(program, diffusename.c_str());
		GLuint specularidx = gl::GetUniformLocation(program, specularname.c_str());
		GLuint shineidx = gl::GetUniformLocation(program, shinename.c_str());
		CheckError();
		gl::Uniform4fv(ambiantidx, 1, mat.data.ambiant.data());
		gl::Uniform4fv(diffuseidx, 1, mat.data.diffuse.data());
		gl::Uniform4fv(specularidx, 1, mat.data.specular.data());
		gl::Uniform1fv(shineidx, 1, &mat.data.shine);
		CheckError();
	}
	void BindMVP(GLuint program, const LibCommon::Transforms& trans, const std::string& name) {
		std::string modelname = name + ".model";
		std::string viewname = name + ".view";
		std::string projname = name + ".proj";
		GLuint modelidx = gl::GetUniformLocation(program, modelname.c_str());
		GLuint viewidx = gl::GetUniformLocation(program, viewname.c_str());
		GLuint projidx = gl::GetUniformLocation(program, projname.c_str());
		CheckError();
		gl::UniformMatrix4fv(modelidx, 1, gl::FALSE_, trans.model.data());
		gl::UniformMatrix4fv(viewidx, 1, gl::FALSE_, trans.view.data());
		gl::UniformMatrix4fv(projidx, 1, gl::FALSE_, trans.proj.data());
		CheckError();
	}
}