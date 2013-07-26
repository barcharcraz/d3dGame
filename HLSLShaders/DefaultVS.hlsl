cbuffer constants {
	float4x4 mvp;
}
struct VertexInput {
	float4 pos : POSITION;
	float4 uv : COLOR;
};
float4 main( VertexInput input ) : SV_POSITION
{
	float4 retval = mul(mvp, input.pos);
	retval /= retval.w;
	return retval;
}