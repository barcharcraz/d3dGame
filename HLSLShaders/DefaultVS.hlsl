cbuffer constants {
	float4x4 mvp;
}

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	float4 retval = mul(mvp, pos);
	retval /= retval.w;
	return retval;
}