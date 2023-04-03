#ifndef _SKILLBOX_FX_
#define _SKILLBOX_FX_

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

// SkillBox Params
// g_float_0 : Skill Cooldown Progress
// g_int_0   : IsActive (bool)


float4 PS_Main(VS_OUT _in) : SV_Target
{
    float4 vColor = g_tex_0.Sample(g_sam_0, _in.uv);
    
    if (vColor.a < 0.1f)
        discard;
    
    bool bIsActive = g_int_3;
    float fCooldownProgress = g_float_0;
    float fPI = 3.1415926535f;
    
    if (!bIsActive)
    {
        float2 vTargetVector = normalize(_in.uv - float2(0.5f, 0.5f));
        float2 vStandardVector = float2(0.0f, -1.0f);
        float3 vCrossProduct = cross(float3(vStandardVector, 0.0f), float3(vTargetVector, 0.0f));
        
        float fSinTheta = vCrossProduct.z;
        float fRadian = acos(dot(vTargetVector, vStandardVector));
        
        if (fSinTheta < 0.f)
            fRadian = (2.f * fPI) - fRadian;
        
        float fCooltimeToRadian = fCooldownProgress * (fPI * 2.f);
        float fGrayScale = (vColor.r + vColor.g + vColor.b) / 3.f;
        vColor.xyz = float3(fGrayScale, fGrayScale, fGrayScale);
        
        if (fCooltimeToRadian < fRadian)
            vColor.xyz /= 5.f;
    }
 
    return vColor;
}
#endif