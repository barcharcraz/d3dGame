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
    float4 wPos : TEXCOORD0;
    float4 norm : NORMAL;
    float3 uv : TEXCOORD1;
};
VertexOutput main( VertexInput input )
{
    VertexOutput retval;
    float4x4 mvp = mul(proj, mul(view, world));
    float4x4 mv = mul(view, world);
    retval.wPos = mul(mv, input.pos);
    retval.pos = mul(mvp, input.pos);
    //retval.pos = mul(view, retval.pos);
    //retval.pos = mul(proj, retval.pos);
    retval.uv = input.uv;
    retval.norm.xyz = mul((float3x3)mv, input.norm.xyz);
    retval.norm.w = 0;
    return retval;
}
