cbuffer matrixBuffer {
	matrix world;
	matrix view;
	matrix projection;
};

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	pos.w=1.0f;
	float4 output = pos;
	output = mul(output,world);
	output = mul(output,view);
	output = mul(output,projection);
	return output;
}