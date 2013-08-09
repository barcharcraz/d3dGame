#ifndef LIBEFFECTS_EFFECTSMANAGEMENT_H
#define LIBEFFECTS_EFFECTSMANAGEMENT_H
#include <LibComponents/Shaders.h>
#include <set>
#include "Shader.h"
#include "Effect.h"
namespace Effects {
	class HLSLShader;
	class GLSLShader;
	
    //! \brief add an HLSL shader with capcaity cap to the shader cache
    //! if there is no matching shader already in the cache than We create one
    //! with a null glslshader and add it, if there is a shader in the cache with
    //! a null hlsl shader than we use that one, otherwise we do nothing
    void AddEffect(const Effect& effect);
	Effect ChooseEffect(const std::set<ShaderCaps>& requestedCaps);
}

#endif