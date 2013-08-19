#include "LightStructs.hlsl"

#if !defined ( HLSL_FORWARDLIGHTING_H )
#define HLSL_FORWARDLIGHTING_H

inline float4 phongLight(in material mat, in float4 lvec, in float4 norm, in float4 ldiffuse) {
	return saturate(mat.diffuse * dot(lvec, norm) * ldiffuse);
}
inline float4 pointLighting(in StructuredBuffer<pointLight> lights, 
	in float4 normal,
	in float4 worldPos, 
	in material mat ) {
	uint stride = 0;
	uint size = 0;
	float4 retval = float4(0, 0, 0, 0);
	lights.GetDimensions(size, stride);
	for (uint i = 0; i < size; ++i) {
		float4 diffuse = lights[i].diffuse;
		float4 lpos = lights[i].position;
		float4 lvec = normalize(lpos - worldPos) * -1;
		retval += phongLight(mat, lvec, normal, diffuse);
	}
	return retval;
}
inline float4 directionalLighting(in StructuredBuffer<directionalLight> lights,
	in float4 norm,
	in material mat) 
{
	float4 retval = float4(0, 0, 0, 0);
	uint stride = 0;
	uint size = 0;
	lights.GetDimensions(size, stride);
	for (uint i = 0; i < size; ++i) {
		float4 lvec = lights[i].direction;
		retval += phongLight(mat, lvec, norm, lights[i].diffuse);
	}
	return retval;
}

#endif