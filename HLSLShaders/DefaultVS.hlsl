cbuffer constants {
	float4x4 mvp;
}

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	float4 retval = mul(mvp, pos);
	retval += float4(0, 0, 0.5, 0);
	return retval;
}