#include "EffectCache.h"
#include <Utils/sets.h>
#include <Utils/exceptions.h>
#include "EffectsManagement.h"
namespace Effects {
	EffectCache::EffectCache() {
		if (GetActiveCache() == nullptr) {
			ActivateCache(this);
		}
	}
	EffectCache::~EffectCache() {
		if (GetActiveCache() == this) {
			DeactivateCache();
		}
	}
	void EffectCache::AddEffect(const Effect& effect) {
		if (cache.count(effect.caps) == 0) {
			cache.insert({ effect.caps, effect });
		}
	}
	Effect EffectCache::ChooseEffect(const std::set<ShaderCaps>& requestedCaps) {
		if (cache.count(requestedCaps) != 0) {
			//there is an exact match, we can just return that
			return cache.at(requestedCaps);
		}
		for (auto& elm : cache) {
			if (utils::subset(requestedCaps, elm.first)) {
				return elm.second;
			}
		}
		throw utils::not_found_error("shader with requested caps was not found");

	}
}