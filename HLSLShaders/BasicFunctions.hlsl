#if !defined (HLSL_BASICFUNCTIONS_H)
#define HLSL_BASICFUNCTIONS_H

struct mvp_s {
    float4x4 world;
    float4x4 view;
    float4x4 proj;
};

inline float4 applyTransform(in mvp_s mvp, int float4 pos) {
    float4x4 fullMtx = mul(mvp.proj, mul(mvp.view, mvp.world));
    return mul(fullMtx, pos);
}


#endif