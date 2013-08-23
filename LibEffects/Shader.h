#ifndef LIBEFFECTS_SHADER_H
#define LIBEFFECTS_SHADER_H
#include <string>
#include <vector>
#include <cstdint>
namespace Effects {
	class HLSLPixelShader;
	class GLSLPixelShader;
	class HLSLVertexShader;
	class GLSLVertexShader;
	//! \brief this structure works in the same
	//! way as a D3D11_INPUT_ELEMENT_DESC but is used
	//! for GLSL attributes as well. For GLSL only the first
	//! two fields are important
	struct ShaderDesc {
		std::string ElementName;
		unsigned int Index;
		uint32_t Format; //will be a DXGI_FORMAT on windows
		unsigned int InputSlot;
		unsigned int AlignedByteOffset;
		int InputSlotClass;
		unsigned int InstanceDataStepRate;
	};
	enum class ShaderCaps {
		MESH_INDEXED,
		MESH_UNINDEXED,
		TEXTURE_MAPPED,
		LIT_DIRECTIONAL,
		LIT_POINT,
		MAT_DIFFUSE,
		MAT_SPEC,
		MAT_AMBIANT,
		DEBUG_SOLID
	};
	struct VertexShader {
		explicit VertexShader(const std::string& filename, const std::vector<ShaderDesc>& desc);
		void Load(const std::string& filename, const std::vector<ShaderDesc>& desc);
		HLSLVertexShader* hvs;
		GLSLVertexShader* gvs;
	};
	struct PixelShader {
		explicit PixelShader(const std::string& filename);
		void Load(const std::string& filename);
		HLSLPixelShader* hps;
		GLSLPixelShader* gps;
	};
}

#endif