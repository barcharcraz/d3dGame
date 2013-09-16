cbuffer constants {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
struct VertexInput {
	float4 pos : POSITION;
};
struct VertexOutput {
	float4 pos : SV_POSITION;
};
VertexOutput main(VertexInput input) {
	VertexOutput rv;
	rv.pos = mul(world, input.pos);
	rv.pos = mul(view, rv.pos);
	rv.pos = mul(proj, rv.pos);
	return rv;
}