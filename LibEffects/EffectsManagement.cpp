#include "EffectsManagement.h"
#include <map>
#include <Utils/exceptions.h>
#include <Utils/sets.h>
namespace Effects {
	static std::multimap<std::set<ShaderCaps>, Shader> shaderCache;
	void AddShader(const std::set<ShaderCaps>& caps, const Shader& shader) {
		if (shaderCache.count(caps) == 0) {
			shaderCache.emplace(caps, shader);
		} else {
			auto range = shaderCache.equal_range(caps);
			for (auto& i = range.first; i != range.second; ++i) {
				if (i->second == shader) {
					return; //the shader is already in the set
					//TODO: Emit warning here
				}
			}
			shaderCache.emplace(caps, shader);
		}
	}

	Shader ChooseShader(const std::set<ShaderCaps>& requestedCaps) {
		for (auto& elm : shaderCache) {
			if (utils::subset(requestedCaps, elm.first)) {
				return elm.second;
			}
		}
		throw utils::not_found_error("shader with requested caps was not found");
		
	}
}