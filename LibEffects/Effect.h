#ifndef LIBEFFECTS_EFFECT_H
#define LIBEFFECTS_EFFECT_H

#include "Shader.h"
#include <string>
#include <vector>
#include <set>
namespace Effects {
	
	class Effect {
	public:
		Effect(const std::string& vsfile, const std::string& psfile,
			const std::vector<ShaderDesc>& desc,
			const std::set<ShaderCaps>& scaps);
		std::set<ShaderCaps> caps;
		VertexShader vs;
		PixelShader ps;
	};
}

#endif