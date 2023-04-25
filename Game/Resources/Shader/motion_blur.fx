#ifndef _MOTION_BLUR_FX_
#define _MOTION_BLUR_FX_

#include "params.fx"

struct VS_IN
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
    float4 dir : DIRECTION;
};



VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    int iDirection = g_int_1;
    
    output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
    output.normal = normalize(mul(float4(_in.normal, 0.f), g_matWV)).xyz;
    if (iDirection == 0)
        output.uv = _in.uv;
    else if (iDirection == 1)
        output.uv = float2(1.0f - _in.uv.x, _in.uv.y);
    
    float4 vNewProjPos = output.pos;
    
    float4 vOldViewPos = mul(float4(_in.pos, 1.f), g_matOldWorld);
    vOldViewPos = mul(vOldViewPos, g_matOldView);
    
    float4 vOldProjPos = mul(vOldViewPos, g_matProjection);
    
    float3 vDir = vNewProjPos.xyz - vOldProjPos.xyz;
    float fCheck = dot(normalize(vDir), normalize(output.normal));
    
    if (fCheck < 0.f)
        output.pos = vOldProjPos;
    else
        output.pos = vNewProjPos;
    
    float2 vVelocity = vNewProjPos.xy - vOldProjPos.xy;
    
    output.dir.xy = vVelocity * 0.5f;
    output.dir.y *= -1.f;
    output.dir.z = output.pos.z;
    
    return output;
}

Texture2D g_tex_0 : register(t0);
SamplerState g_sam_0 : register(s0);

struct PS_OUT
{
    float4 vVelocity : SV_Target0;
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
    
    float2 vUV = (vLeftTopPos + vOffset) + (_in.uv * vSpriteSize);
    
    float4 vColor = g_tex_0.Sample(g_sam_0, vUV);
    if (vColor.a < 0.1f)
        discard;
    output.vVelocity.xy = _in.dir.xy;
    output.vVelocity.z = 1.f;
    
    return output;
}
#endif