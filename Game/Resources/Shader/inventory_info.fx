#ifndef _INVENTORY_INFO_FX_
#define _INVENTORY_INFO_FX_

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
Texture2D g_tex_1 : register(t1);

SamplerState g_sam_0 : register(s0);

VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    
    output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
    output.uv = _in.uv;
    
    return output;
}

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float4 vColor = g_tex_0.Sample(g_sam_0, _in.uv);
    
    if (g_tex_on_1 && 
        _in.uv.x > 0.05f && _in.uv.x < 0.95f && 
        _in.uv.y > 0.05f && _in.uv.y < 0.95f)
        vColor = g_tex_1.Sample(g_sam_0, _in.uv);
    
    if (vColor.a <= 0.1f)
        discard;

    return vColor;
}
#endif