cbuffer constants {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
struct VertexInput {
	float4 pos : POSITION;
	float4 norm : NORMAL;
	float3 uv : TEXCOORD;
};
struct VertexOutput {
	float4 pos : SV_POSITION;
	float4 norm : NORMAL;
	float3 uv : TEXCOORD1;
};
VertexOutput main(VertexInput input) {
	VertexOutput retval;
	retval.pos = mul(world, input.pos);
	//retval.pos.xyz = mul((float3x3)transpose(view), retval.pos.xyz);
	retval.pos = mul(view, retval.pos);
	
	retval.pos = mul(proj, retval.pos);
	retval.norm.xyz = mul((float3x3)world, input.norm.xyz);
	retval.norm.w = 1;
	retval.norm = normalize(retval.norm);
	retval.uv = input.uv;
	return retval;
}