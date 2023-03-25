#ifndef _COMPUTE_FX_
#define _COMPUTE_FX_

#include "params.fx"

Texture2D g_tex_1 : register(t1);
SamplerState g_sam_0 : register(s0);
RWTexture2D<float4> g_rwtex_0 : register(u0);

// Irregular Shader
// g_tex_1   : Noise   Texture (SRV)
// g_rwtex_0 : Created Texture (UAV | SRV)
// g_vec3_0  : Texture Size

[numthreads(1024, 1, 1)]
void CS_Main(uint3 threadIndex : SV_DispatchThreadID)
{
    float3 vTexSize = g_vec3_0;
    float2 vUV = threadIndex.xy / float2(vTexSize.x, vTexSize.y);
    float fNoise = g_tex_1.SampleLevel(g_sam_0, vUV, 0).r;

    float4 fColor = float4(0.f, 0.f, 0.f, 1.f);
    if (fNoise < 0.1f)
        fColor = float4(1.f, 0.f, 0.f, 1.f);
    else if (fNoise < 0.2f)
        fColor = float4(0.f, 1.f, 0.f, 1.f);
    else if (fNoise < 0.3f)
        fColor = float4(0.f, 0.f, 1.f, 1.f);
    else if (fNoise < 0.4f)
        fColor = float4(0.f, 0.f, 1.f, 1.f);
    else if (fNoise < 0.5f)
        fColor = float4(1.f, 0.f, 1.f, 1.f);
    else if (fNoise < 0.6f)
        fColor = float4(0.f, 1.f, 1.f, 1.f);
    else if (fNoise < 0.7f)
        fColor = float4(0.5f, 0.f, 0.5f, 1.f);
    else if (fNoise < 0.8f)
        fColor = float4(0.f, 0.5f, 0.5f, 1.f);
    else if (fNoise < 0.9f)
        fColor = float4(1.f, 0.f, 0.5f, 1.f);
    else
        fColor = float4(0.5f, 1.f, 5.f, 1.f);

    g_rwtex_0[threadIndex.xy] = fColor;
}
#endif