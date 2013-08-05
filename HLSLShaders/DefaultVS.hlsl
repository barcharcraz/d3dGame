cbuffer constants {
	float4x4 mvp;
}
struct VertexInput {
	float4 pos : POSITION;
	float3 uv : TEXCOORD;
};
struct VertexOutput {
	float4 Pos : SV_POSITION;
	float3 uv : TEXCOORD;
};
VertexOutput main( VertexInput input )
{
	VertexOutput retval;
	retval.Pos = mul(mvp, input.pos);
	retval.uv = input.uv;
	return retval;
}