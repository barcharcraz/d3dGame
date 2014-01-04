#include "LightStructs.hlsl"
#include "ForwardLighting.hlsl"
Texture2D tex;
SamplerState samp;
cbuffer objMat {
	material mat;
};

StructuredBuffer<pointLight> pointLights;
StructuredBuffer<directionalLight> dirLights;
struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float4 wPos : TEXCOORD0;
	float4 norm : NORMAL;
	float3 uv : TEXCOORD1;
};
float4 main(VS_OUTPUT input) : SV_TARGET
{
	float4 color;
	float4 texColor;
	float intensity;
	color = mat.ambiant;
	color += pointLighting(pointLights, input.norm, input.wPos, mat);
	color += directionalLighting(dirLights, input.norm, input.wPos, mat);
	texColor = tex.Sample(samp, input.uv.xy);
	color = saturate(color);
	color *= texColor;
	color.a = 1;
	//color = input.norm;
	return color;
}