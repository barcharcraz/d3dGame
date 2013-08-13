#include "EffectsManagement.h"
#include <map>
#include <Utils/exceptions.h>
#include <Utils/sets.h>
namespace Effects {
	static std::map<std::set<ShaderCaps>, Effect> shaderCache;
	void AddEffect(const Effect& effect) {
        if(shaderCache.count(effect.caps) == 0) {
            shaderCache.emplace(effect.caps, effect);
        }
    }
	Effect ChooseEffect(const std::set<ShaderCaps>& requestedCaps) {
		if (shaderCache.count(requestedCaps) != 0) {
			//there is an exact match, we can just return that
			return shaderCache.at(requestedCaps);
		}
		for (auto& elm : shaderCache) {
			if (utils::subset(requestedCaps, elm.first)) {
				return elm.second;
			}
		}
		throw utils::not_found_error("shader with requested caps was not found");
		
	}
}