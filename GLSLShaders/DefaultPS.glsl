#version 140
#pragma debug(on)
#include "LightStructs.glslh"
#include "ForwardLighting.glslh"
in vec4 normal;
in vec4 uvOut;
in vec4 viewPos;
out vec4 outputColor;
uniform directionalLight_t dlights[NUM_DIRECTIONAL];
uniform pointLight_t plights[NUM_POINT];
uniform material_t mat;
uniform sampler2D tex;
void main() {
    outputColor = mat.ambiant;
    for(int i = 0; i < NUM_POINT; ++i) {
        outputColor += pointLight(plights[i], normal, viewPos, mat); 
    }
    for(int i = 0; i < NUM_DIRECTIONAL; ++i) {
        outputColor += directionalLight(dlights[i], normal, viewPos, mat); 
    }
    outputColor = clamp(outputColor, 0.0, 1.0);
    outputColor = outputColor * texture(tex, uvOut.xy);
    outputColor.a = 1;
  
}
