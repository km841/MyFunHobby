#ifndef _FORWARD_FX_
#define _FORWARD_FX_

#include "params.fx"

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
};

Texture2D g_tex_0 : register(t0);
SamplerState g_sam_0 : register(s0);

VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    
    output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
    output.uv = _in.uv;
    
    return output;
}

// HP Shader
// g_float_0 : HP Ratio
// g_vec2_0  : Texture Size
// g_vec2_1  : Resolution
// g_vec2_2  : Current Pos

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float fRatio = g_float_0;
    float2 vTexSize = g_vec2_0;
    float2 vResolution = g_vec2_1;
    float2 vMyPos = g_vec2_2;
   
    float fWidthLimit = (vTexSize.x + vMyPos.x) * fRatio / vResolution.x;
    if (fWidthLimit < _in.uv.x)
        discard;
    
    return g_tex_0.Sample(g_sam_0, _in.uv);
}
    
#endif