struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float3 uv : TEXCOORD;
};
float4 main(VS_OUTPUT input) : SV_TARGET
{
	return float4(input.uv.x, input.uv.y, 1.0f, 1.0f);
}