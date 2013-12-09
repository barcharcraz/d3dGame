#include "LightStructs.hlsl"

#if !defined ( HLSL_FORWARDLIGHTING_H )
#define HLSL_FORWARDLIGHTING_H
inline float4 phongLight(in material mat, 
    in float4 viewDir, 
    in float4 lvec, 
    in float4 norm,
    in float4 ldiffuse, 
    in float4 lspec)
{
    float cosAngIncidence = dot(lvec, norm);
    cosAngIncidence = saturate(cosAngIncidence);
    float4 rv = (mat.diffuse * cosAngIncidence * ldiffuse);
    if (cosAngIncidence > 0) {
        float4 refvec = reflect(lvec, norm);
        float phong = dot(refvec, viewDir);
        phong = pow(max(phong, 0.0), 50);
        float4 spec = mat.specular * phong * lspec;
        spec = saturate(spec);
        rv += spec;
    }
    rv = saturate(rv);
    return rv;
}
inline float4 pointLighting(in StructuredBuffer<pointLight> lights, 
    in float4 normal,
    in float4 worldPos, 
    in material mat ) {

    uint stride = 0;
    uint size = 0;
    float4 retval = float4(0, 0, 0, 0);
    lights.GetDimensions(size, stride);
    for (uint i = 0; i < size; ++i) {
        float4 diffuse = lights[i].diffuse;
        float4 spec = lights[i].specular;
        float4 lpos = lights[i].position;
        float4 lvec = normalize(lpos - worldPos) * -1;
        retval += phongLight(mat, normalize(worldPos), lvec, normal, diffuse, spec);
    }
    return retval;
}
inline float4 directionalLighting(in StructuredBuffer<directionalLight> lights,
    in float4 norm,
    in float4 worldPos,
    in material mat) 
{
    float4 retval = float4(0, 0, 0, 0);
    uint stride = 0;
    uint size = 0;
    lights.GetDimensions(size, stride);
    for (uint i = 0; i < size; ++i) {
        float4 lvec = lights[i].direction;
        retval += phongLight(mat, normalize(-worldPos), normalize(lvec), normalize(norm), lights[i].diffuse, lights[i].specular);
    }
    return retval;
}

#endif