#version 140
#include "LightStructs.glslh"
in vec4 normal;
in vec4 uvOut;
out vec4 outputColor;
uniform directionalLight_t dlights[NUM_DIRECTIONAL];
uniform pointLight_t plights[NUM_POINT];
uniform material_t mat;
uniform sampler2D tex;
void main() {
  outputColor = texture(tex, uvOut.xy);
  
}
