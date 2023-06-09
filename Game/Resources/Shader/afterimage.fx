#ifndef _AFTERIMAGE_FX_
#define _AFTERIMAGE_FX_

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
    int iDirection = g_int_1;
    
    VS_OUT output = (VS_OUT) 0;
    
    output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
    
    if (iDirection == 0)
        output.uv = _in.uv;
    else if (iDirection == 1)
        output.uv = float2(1.0f - _in.uv.x, _in.uv.y);
    
    return output;
}

// Animation Params
// g_vec2_0 : LT Pos
// g_vec2_1 : Sprite size
// g_vec2_2 : Atlas Size
// g_vec2_3 : Offset
// g_int_0  : Animation Flag
// g_int_1  : Direction
// g_int_2  : AfterImage Type
// g_float_0: Ratio

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float2 vLeftTopPos = g_vec2_0;
    float2 vSpriteSize = g_vec2_1;
    float2 vAtlasSize = g_vec2_2;
    float2 vOffset = g_vec2_3;
    int iAnimationFlag = g_int_0;
    int iAfterImageType = g_int_2;
    
    float fRatio = g_float_0;
    
    float4 vColor;
    if (iAnimationFlag)
    {
        float2 vUV = (vLeftTopPos + vOffset) + (_in.uv * vSpriteSize);
        vColor = g_tex_0.Sample(g_sam_0, vUV);
        if (vColor.a < 0.1f)
            discard;
        
        if (vColor.a > 0.f && fRatio > 0.f)
            vColor.a = 1.f * fRatio;
         
    }
    else
    {
        vColor = g_tex_0.Sample(g_sam_0, _in.uv);
        if (vColor.a <= 0.01f)
            discard;
        
        if (vColor.a > 0.f && fRatio >= 0.f)
            vColor.a = 1.f * fRatio;
    }
    
    if (iAfterImageType)
        vColor.rgb = float3(0.63f, 0.13f, 0.75f);
    else
        vColor.rgb = float3(0.f, 0.f, 0.f);
    
    return vColor;
}
#endif