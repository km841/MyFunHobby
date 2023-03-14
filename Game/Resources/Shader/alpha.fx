#ifndef _ALPHA_FX_
#define _ALPHA_FX_

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

VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    
    output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
    output.uv = _in.uv;
    
    return output;
}

Texture2D g_tex_0 : register(t0);
SamplerState g_sam_0 : register(s0);

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float4 color = g_tex_0.Sample(g_sam_0, _in.uv);
    
    if (color.a == 0)
    {
        discard;
    }
    
    return color;
}
#endif