#ifndef LIBCOMPONENTS_SHADERS_H
#define LIBCOMPONENTS_SHADERS_H
#include "IComponent.h"
#include <memory>
namespace LibShaders {
    struct HLSLShaderSet;
    struct GLSLShaderSet;
}
namespace Components {
	class Shaders : public IComponent {
	public:
		Shaders(LibShaders::HLSLShaderSet* hlsl);
		LibShaders::HLSLShaderSet* HLSL();
	private:
		LibShaders::HLSLShaderSet* _HLSL;
	};
}

#endif
