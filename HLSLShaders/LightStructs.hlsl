#if !defined( HLSL_LIGHTSTRUCTS_H )
#define HLSL_LIGHTSTRUCTS_H

struct pointLight {
	float4 diffuse;
	float4 position;
};
struct directionalLight {
	float4 diffuse;
	float4 direction;
};
struct material {
	float4 ambiant;
	float4 diffuse;
};
#endif