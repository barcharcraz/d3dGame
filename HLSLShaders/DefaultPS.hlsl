Texture2D tex;
SamplerState samp;
struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float3 uv : TEXCOORD;
};
float4 main(VS_OUTPUT input) : SV_TARGET
{
	float4 color;
	color = tex.Sample(samp, input.uv);
	return color;
}