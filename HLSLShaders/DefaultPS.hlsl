Texture2D tex;
SamplerState samp;

cbuffer light {
	float4 diffuse;
	float3 direction;
};

struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float4 norm : NORMAL;
	float3 uv : TEXCOORD;
};
float4 main(VS_OUTPUT input) : SV_TARGET
{
	float4 color;
	float4 lightDir;
	float4 texColor;
	float intensity;
	texColor = tex.Sample(samp, input.uv.xy);
	lightDir.xyz = direction.xyz;
	lightDir.w = 1;
	lightDir *= -1;
	intensity = saturate(dot(input.norm, lightDir));
	color = saturate(diffuse * intensity);
	color *= texColor;
	//color = input.norm;
	return color;
}