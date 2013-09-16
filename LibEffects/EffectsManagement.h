#ifndef LIBEFFECTS_EFFECTSMANAGEMENT_H
#define LIBEFFECTS_EFFECTSMANAGEMENT_H
#include <LibComponents/Shaders.h>
#include <set>
#include "Shader.h"
#include "Effect.h"
#include "EffectCache.h"
namespace Effects {
	
    //! \brief add a shader to the cache
	//!
	//! add an HLSL shader with capcaity cap to the shader cache
    //! if there is no matching shader already in the cache than We create one
    //! with a null glslshader and add it, if there is a shader in the cache with
    //! a null hlsl shader than we use that one, otherwise we do nothing
	//!
	//! If there is no active shader cache we will throw an exception
    void AddEffect(const Effect& effect);

	//! \brief get a shader with specified caps
	//!
	//! note that this function gets a shader that has AT LEAST these caps
	//! it may also have other caps, if there is a shader with the exact requested caps
	//! then we will return that one
	Effect ChooseEffect(const std::set<ShaderCaps>& requestedCaps);

	//! \brief Set an EffectCache to be active. This means that
	//! that effect cache will be used by default for all global
	//! add and remove operations
	void ActivateCache(EffectCache* cache);
	//! \brief clear the active cache
	void DeactivateCache();

	//! \brief retrives the active shader cache
	EffectCache* GetActiveCache();
}

#endif