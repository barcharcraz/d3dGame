#include "Shader.h"

namespace Effects {
    Shader::Shader(HLSLShader* shader)
        : hlsl(shader), glsl(nullptr)
    {
        
    }
    Shader::Shader(GLSLShader* shader)
        : hlsl(nullptr), glsl(shader)
    {
        
    }
}