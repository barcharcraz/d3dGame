Texture2D tex;
SamplerState samp;

struct VS_OUTPUT {
	float4 pos : SV_POSITION;
	float4 norm : NORMAL;
	float4 uv : TEXCOORD;
};
float4 main(VS_OUTPUT input) : SV_TARGET {
	return tex.Sample(samp, input.uv.xy);
}