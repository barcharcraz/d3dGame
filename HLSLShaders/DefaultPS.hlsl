Texture2D tex;
SamplerState samp;

cbuffer light {
	float4 diffuse;
	float3 direction;
};
cbuffer material {
	float4 mambiant;
	float4 mdiffuse;
};
struct pointLight {
	float4 position;
	float4 diffuse;
};
StructuredBuffer<pointLight> pointLights;
struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float4 norm : NORMAL;
	float3 uv : TEXCOORD;
};
float4 main(VS_OUTPUT input) : SV_TARGET
{
	float4 color;
	float4 texColor;
	float intensity;
	color = mambiant;
	texColor = tex.Sample(samp, input.uv.xy);
	intensity = saturate(dot((float3)input.norm, direction));
	color += (diffuse * intensity);
	color = saturate(color);
	color *= texColor;
	//color = input.norm;
	return color;
}