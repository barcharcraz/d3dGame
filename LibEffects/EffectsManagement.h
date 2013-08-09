#ifndef LIBEFFECTS_EFFECTSMANAGEMENT_H
#define LIBEFFECTS_EFFECTSMANAGEMENT_H
#include <LibComponents/Shaders.h>
#include <set>
#include "Shader.h"
namespace Effects {
	class HLSLShader;
	class GLSLShader;
	enum class ShaderCaps {
		MESH_INDEXED,
		MESH_UNINDEXED,
		TEXTURE_MAPPED,
		LIT_DIRECTIONAL,
		LIT_POINT,
		MAT_DIFFUSE,
		MAT_SPEC,
		MAT_AMBIANT
	};
    //! \brief add an HLSL shader with capcaity cap to the shader cache
    //! if there is no matching shader already in the cache than We create one
    //! with a null glslshader and add it, if there is a shader in the cache with
    //! a null hlsl shader than we use that one, otherwise we do nothing
    void AddShader(const std::set<ShaderCaps>& caps, HLSLShader* shader);
    //! \brief Adds a GLSL shader with capacity cap to the shader cache
    //! these functions do not take ownership of the shader
    void AddShader(const std::set<ShaderCaps>& caps, GLSLShader* shader);
	void AddShader(const std::set<ShaderCaps>& caps, const Shader& shader);
	Shader ChooseShader(const std::set<ShaderCaps>& requestedCaps);
}

#endif