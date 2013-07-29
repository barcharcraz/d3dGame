#include "stdafx.h"
#include "Shaders.h"
#include <stdexcept>
namespace Components {
	Shaders::Shaders(std::shared_ptr<LibShaders::HLSLShaderSet> hlsl)
		: _HLSL(hlsl)
	{

	}
	LibShaders::HLSLShaderSet* Shaders::HLSL() {
		if (_HLSL == nullptr) {
			throw std::runtime_error("Entity does not contain an HLSL shader, perhaps you forgot to add one");
		}
	}
}