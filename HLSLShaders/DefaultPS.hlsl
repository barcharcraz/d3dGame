struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};
float4 main(VS_OUTPUT input) : SV_TARGET
{
	return float4(input.Color.x, input.Color.y, 1.0f, 1.0f);
}