#include "EffectsManagement.h"
#include "EffectCache.h"
#include "Effect.h"
#include <map>
#include <Utils/exceptions.h>
#include <Utils/sets.h>
namespace Effects {
	static EffectCache* activeCache;
	void AddEffect(const Effect& effect) {
		if (activeCache == nullptr) {
			throw utils::precondition_error("There is no active shader cache");
		}
		activeCache->AddEffect(effect);
	}
	Effect ChooseEffect(const std::set<ShaderCaps>& caps) {
		if (activeCache == nullptr) {
			throw utils::precondition_error("there is no active shader cache");
		}
		return activeCache->ChooseEffect(caps);
	}

	EffectCache* GetActiveCache() {
		return activeCache;
	}

	void ActivateCache(EffectCache* cache) {
		activeCache = cache;
	}
	void DeactivateCache() {
		activeCache = nullptr;
	}
}