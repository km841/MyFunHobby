#ifndef _EFFECT_FX_
#define _EFFECT_FX_

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
Texture2D g_tex_2 : register(t2);
SamplerState g_sam_0 : register(s0);

VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    
    output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
    output.uv = _in.uv;

    return output;
}

// Animation Params
// g_vec2_0 : LT Pos
// g_vec2_1 : Sprite size
// g_vec2_2 : Atlas Size
// g_vec2_3 : Offset
// g_int_0  : Animation Flag
// g_int_1  : Direction
// g_int_2  : Current Frame
// g_float_0: Ratio

struct PS_OUT
{
    float4 vEffectColor : SV_Target0;
};


PS_OUT PS_Main(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0;
    
    float2 vLeftTopPos = g_vec2_0;
    float2 vSpriteSize = g_vec2_1;
    float2 vAtlasSize = g_vec2_2;
    float2 vOffset = g_vec2_3;
    int iAnimationFlag = g_int_0;
    int iEffectFlag = g_int_3;
    
    float4 vColor;
    if (iAnimationFlag)
    {
        float2 vUV = (vLeftTopPos + vOffset) + (_in.uv * vSpriteSize);
        vColor = g_tex_0.Sample(g_sam_0, vUV);
        if (vColor.a < 0.1f)
            discard;
       
    }
    else
    {
        vColor = g_tex_0.Sample(g_sam_0, _in.uv);
        if (vColor.a <= 0.1f)
            discard;
       
    }
    
    output.vEffectColor = vColor;
   
    return output;
}
#endif