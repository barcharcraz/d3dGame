#ifndef EFFECTS_EFFECTCACHE_H
#define EFFECTS_EFFECTCACHE_H
#include "Shader.h"
#include "Effect.h"
#include <map>
#include <set>
namespace Effects {
	class EffectCache {
	public:
		EffectCache();
		~EffectCache();
		Effect ChooseEffect(const std::set<ShaderCaps>& requestedCaps);
		void AddEffect(const Effect& effect);
	private:
		std::map<std::set<ShaderCaps>, Effect> cache;
	};
}

#endif