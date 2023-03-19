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
Texture2D g_tex_1 : register(t1);

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

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float2 vLeftTopPos = g_vec2_0;
    float2 vSpriteSize = g_vec2_1;
    float2 vAtlasSize = g_vec2_2;
    float2 vOffset = g_vec2_3;
    int iAnimationFlag = g_int_0;
    int iDirection = g_int_1;
    
    
    
    int iRight = 0;
    int iLeft = 1;
    
    if (iAnimationFlag == 1)
    {
        float2 vUV;
        if (iDirection == iLeft)
        {
            vUV = (vLeftTopPos + vOffset) + (_in.uv * vSpriteSize);
        }
        else if (iDirection == iRight)
        {
            vUV = (vLeftTopPos + -vOffset) + (_in.uv * vSpriteSize);
            vUV.x = 1.f - vUV.x;
        }
        
        float4 vColor = g_tex_0.Sample(g_sam_0, vUV);
        if (vColor.w == 0)
            discard;
        
        return vColor;
    }
    else
    {
        float4 vColor = g_tex_0.Sample(g_sam_0, _in.uv);
        if (vColor.w == 0)
            discard;
        return vColor;
    }
}
#endif