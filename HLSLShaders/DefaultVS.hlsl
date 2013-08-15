cbuffer constants {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
}
struct VertexInput {
	float4 pos : POSITION;
	float4 norm : NORMAL;
	float3 uv : TEXCOORD;
};
struct VertexOutput {
	float4 pos : SV_POSITION;
	float4 norm : NORMAL;
	float3 uv : TEXCOORD;
};
VertexOutput main( VertexInput input )
{
	VertexOutput retval;
	retval.pos = mul(world, input.pos);
	retval.pos = mul(view, retval.pos);
	retval.pos = mul(proj, retval.pos);
	retval.uv = input.uv;
	retval.norm = mul(input.norm, world);
	retval.norm.w = 1;
	retval.norm = normalize(retval.norm);
	return retval;
}