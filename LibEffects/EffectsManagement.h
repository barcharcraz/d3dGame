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

	void AddShader(const std::set<ShaderCaps>& caps, const Shader& shader);
	Shader ChooseShader(const std::set<ShaderCaps>& requestedCaps);
}

#endif