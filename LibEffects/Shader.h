#ifndef LIBEFFECTS_SHADER_H
#define LIBEFFECTS_SHADER_H
namespace Effects {
	class HLSLShader;
	class GLSLShader;
	class Shader {
	public:
		HLSLShader* hlsl;
		GLSLShader* glsl;
	};
	inline bool operator==(const Shader& lhs, const Shader& rhs) {
		return (lhs.hlsl == rhs.hlsl && lhs.glsl == rhs.glsl);
	}
}

#endif