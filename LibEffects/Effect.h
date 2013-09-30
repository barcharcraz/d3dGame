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
//hash specialization for effects
namespace std {
	template<>
	struct hash<Effects::Effect> {
		std::size_t operator()(const Effects::Effect& e) const {
			auto& psname = e.ps.name;
			auto& vsname = e.vs.name;
			std::string both = psname + vsname;
			return std::hash<std::string>()(both);
		}
	};
}

#endif
