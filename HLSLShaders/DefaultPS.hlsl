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
	float4 diffuse;
	float3 position;
	
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
	uint size = 0;
	uint stride = 0;
	pointLights.GetDimensions(size, stride);
	for (uint i = 0; i < size; ++i) {
		float3 lvec = normalize(pointLights[i].position - input.Pos.xyz);
		color += saturate(mdiffuse * dot(lvec, input.norm.xyz) * pointLights[i].diffuse);
	}
	float3 lightDir = direction * -1;
	texColor = tex.Sample(samp, input.uv.xy);
	intensity = saturate(dot(normalize(input.norm.xyz), normalize(lightDir)));
	color += (diffuse * intensity);
	color = saturate(color);
	color *= texColor;
	//color = input.norm;
	return color;
}