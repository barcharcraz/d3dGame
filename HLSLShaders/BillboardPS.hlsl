Texture2D tex;
SamplerState samp;

struct VS_OUTPUT {
	float4 pos : SV_POSITION;
	float4 norm : NORMAL;
	float3 uv : TEXCOORD1;
};
float4 main(VS_OUTPUT input) : SV_TARGET {
	return tex.Sample(samp, input.uv.xy);
}