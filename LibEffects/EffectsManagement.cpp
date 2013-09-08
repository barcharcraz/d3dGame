#include "EffectsManagement.h"
#include "EffectCache.h"
#include "Effect.h"
#include <map>
#include <memory>
#include <Utils/exceptions.h>
#include <Utils/sets.h>
#include <Utils/make_unique.h>
namespace Effects {
	static EffectCache* activeCache;
	static std::unique_ptr<EffectCache> _defaultCache;
	void AddEffect(const Effect& effect) {
		if (activeCache == nullptr) {
			_defaultCache = std::make_unique<EffectCache>();
			ActivateCache(_defaultCache.get());
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
		// we delete the default cache, this will
		// be recreated (a new copy) if someone takes
		// their cache out then tries to add a new effect
		if(activeCache == _defaultCache.get()) {
			_defaultCache.reset();
		}
		activeCache = cache;
	}
	void DeactivateCache() {
		activeCache = nullptr;
	}
}