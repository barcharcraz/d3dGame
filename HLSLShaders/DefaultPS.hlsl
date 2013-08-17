Texture2D tex;
SamplerState samp;

cbuffer material {
	float4 mambiant;
	float4 mdiffuse;
};
struct pointLight {
	float4 diffuse;
	float3 position;
	float padding;
};
struct directionalLight {
	float4 diffuse;
	float4 direction;
};
StructuredBuffer<pointLight> pointLights;
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
	color = mambiant;
	uint size = 0;
	uint stride = 0;
	pointLights.GetDimensions(size, stride);
	for (uint i = 0; i < size; ++i) {
		float4 diffuse = pointLights[i].diffuse;
		float3 lpos = pointLights[i].position;
		float3 lvec = normalize(lpos - input.wPos.xyz) * -1;
		color += saturate(mdiffuse * dot(lvec, input.norm.xyz) * diffuse);
	}
	texColor = tex.Sample(samp, input.uv.xy);
	color = saturate(color);
	color *= texColor;
	//color = input.norm;
	return color;
}