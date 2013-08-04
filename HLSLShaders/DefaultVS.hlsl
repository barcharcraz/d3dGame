cbuffer constants {
	float4x4 mvp;
}
struct VertexInput {
	float4 pos : POSITION;
	float4 uv : COLOR;
};
struct VertexOutput {
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};
VertexOutput main( VertexInput input )
{
	VertexOutput retval;
	retval.Pos = mul(mvp, input.pos);
	retval.Color = input.uv;
	return retval;
}