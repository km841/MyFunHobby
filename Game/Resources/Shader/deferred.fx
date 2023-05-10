#ifndef _DEFERRED_FX_
#define _DEFERRED_FX_

#include "params.fx"

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 viewPos : POSITION;
    float3 dir : DIRECTION;
};

Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
SamplerState g_sam_0 : register(s0);

VS_OUT VS_Main(VS_IN _in)
{
    int iDirection = g_int_1;
    
    VS_OUT output = (VS_OUT) 0;
    output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
    output.normal = normalize(mul(float4(_in.normal, 0.f), g_matWV)).xyz;
    
    if (iDirection == 0)
        output.uv = _in.uv;
    else if (iDirection == 1)
        output.uv = float2(1.0f - _in.uv.x, _in.uv.y);
    
    float4 vNewProjPos = output.pos;
    
    float4 vOldViewPos = mul(float4(_in.pos, 1.f), g_matOldWV);
    float4 vOldProjPos = mul(float4(vOldViewPos.xyz, 1.f), g_matProjection);
    
    float3 vDir = vNewProjPos.xyz - vOldProjPos.xyz;
    float fCheck = dot(normalize(vDir), normalize(output.normal));
    
    if (fCheck < 0.f)
        output.pos = vOldProjPos;
    else
        output.pos = vNewProjPos;
    
    float2 vVelocity = vNewProjPos.xy - vOldProjPos.xy;
    
    output.dir.xy = vVelocity * -0.5f;
    output.dir.z = output.pos.z;
    output.viewPos = mul(float4(_in.pos, 1.f), g_matWV).xyz;
    
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
// g_int_3  : Motion Blur Flag
// g_float_0: Ratio

struct PS_OUT
{
    float4 vPosition : SV_Target0;
    float4 vColor : SV_Target1;
    float4 vVelocity : SV_Target2;
};

PS_OUT PS_Main(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0;
    
    float2 vLeftTopPos = g_vec2_0;
    float2 vSpriteSize = g_vec2_1;
    float2 vAtlasSize = g_vec2_2;
    float2 vOffset = g_vec2_3;
    int iAnimationFlag = g_int_0;
    int iPlayerFlag = g_int_2;
    int iMotionBlurFlag = g_int_3;
    
    float fRatio = g_float_0;
    
    float4 vColor;
    if (iAnimationFlag)
    {
        float2 vUV = (vLeftTopPos + vOffset) + (_in.uv * vSpriteSize);
        vColor = g_tex_0.Sample(g_sam_0, vUV);
        if (vColor.a < 0.1f)
            discard;
        
        if (fRatio > 0.f)
            vColor.a = 1.f * fRatio;
    }
    else
    {
        vColor = g_tex_0.Sample(g_sam_0, _in.uv);
        if (vColor.a <= 0.1f)
            discard;
        
        if (fRatio > 0.f)
            vColor.a = 1.f * fRatio;
    }
   
    output.vPosition = float4(_in.viewPos, 0.f);
    output.vColor = vColor;
    
    if (iMotionBlurFlag) 
        output.vVelocity = float4(_in.dir.xy, 1.f, 1.f);
   
    return output;
}
#endif