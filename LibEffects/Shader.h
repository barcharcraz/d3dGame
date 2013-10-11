#ifndef LIBEFFECTS_SHADER_H
#define LIBEFFECTS_SHADER_H
#include <string>
#include <vector>
#include <cstdint>
#include <string>
namespace Effects {
	const unsigned int APPEND_ALIGNED_ELEMENT = 0xFFFFFFFF;
	//! \brief this structure works in the same
	//! way as a D3D11_INPUT_ELEMENT_DESC but is used
	//! for GLSL attributes as well. For GLSL
	//! these struct members match up to the params
	//! of glVertexAttribPointer
	struct ShaderDesc {
		std::string ElementName;
		unsigned int Index;
		uint32_t Format; //will be a DXGI_FORMAT on windows
		unsigned int InputSlot;
		unsigned int AlignedByteOffset;
		int InputSlotClass;
		unsigned int InstanceDataStepRate;
	};
	enum InputFormats : uint32_t {
		R32G32B32A32_FLOAT = 2,
		R32G32B32_FLOAT = 6
	};
	enum SlotClass : int {
		PER_INSTANCE,
		PER_VERTEX
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
		RENDER_BILLBOARD,
		DEBUG_SOLID
	};
	struct VertexShader {
		explicit VertexShader(const std::string& filename, const std::vector<ShaderDesc>& desc);
		std::string name;
		std::vector<ShaderDesc> inputDesc;
		
	};
	struct PixelShader {
		explicit PixelShader(const std::string& filename);
		std::string name;
	};
}

#endif
