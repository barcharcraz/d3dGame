cbuffer constants {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
struct VertexInput {
	float4 pos : POSITION;
	float4 norm : NORMAL;
	float4 uv : TEXCOORD;
};
struct VertexOutput {
	float4 pos : SV_POSITION;
	float4 norm : NORMAL;
	float4 uv : TEXCOORD1;
};
VertexOutput main(VertexInput input) {
	VertexOutput retval;
	retval.pos = mul(world, input.pos);
	retval.pos = mul((float3x3)view, input.pos);
	retval.pos = mul(view, input.pos);
	retval.pos = mul(proj, retval.pos);
}