#pragma once
#include <string>
#include "HLSLPixelShader.h"
#include "HLSLVertexShader.h"
namespace Effects {
	HLSLPixelShader* GetHLSLPixelShader(ID3D11Device* pDev, const std::string& name);
	HLSLVertexShader* GetHLSLVertexShader(ID3D11Device* pDev, const std::string& name, const std::vector<ShaderDesc>& desc);
}