#ifndef _FINAL_FX_
#define _FINAL_FX_

#include "params.fx"
#include "utils.fx"

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
    output.pos = float4(_in.pos, 1.f);
    output.uv = _in.uv;
    
    return output;
}

// Final Shader
// g_tex_0   : Diffuse Color RenderTarget
// g_tex_1   : Velocity RenderTarget
// g_tex_2   : Light Color RenderTarget
// g_float_0 : Fade Ratio

#define DISTORTION_AMOUNT (sin(fAccTime * 0.8) + 1.0) / 2.0

float2 PincushionDistortion(float2 vUV, float fStrength)
{
    float2 fCenter = vUV - 0.5;
    float fAngle = atan2(fCenter.x, fCenter.y);
    float fDot = dot(fCenter, fCenter);
    return 0.5 + float2(sin(fAngle), cos(fAngle)) * sqrt(fDot) * (1.0 - fStrength * fDot);
}

float3 ChromaticAbberation(float2 vUV, float fAccTime)
{
    float fRedChannel = g_tex_0.Sample(g_sam_0, PincushionDistortion(vUV, 0.3 * DISTORTION_AMOUNT)).r;
    float fGreenChannel = g_tex_0.Sample(g_sam_0, PincushionDistortion(vUV, 0.15 * DISTORTION_AMOUNT)).g;
    float fBlueChannel = g_tex_0.Sample(g_sam_0, PincushionDistortion(vUV, 0.075 * DISTORTION_AMOUNT)).b;
    return float3(fRedChannel, fGreenChannel, fBlueChannel);;
}

float4 AfterColor(float2 vUV, float fAccTime)
{
    float3 fColor = ChromaticAbberation(vUV, fAccTime);
    return float4(fColor, 1.0);
}

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float4 output = (float4) 0;

    int iDistortionFlag = g_int_0;
    int iAfterEffectFlag = g_int_1;
    int iWhiteFadeFlag = g_int_2;
    int iBrokenScreenFlag = g_int_3;
    
    float fAccTime = g_float_1;
    float fProgress = g_float_2;
    float fFadeRatio = g_float_0;
    
    float4 vColor = g_tex_0.Sample(g_sam_0, _in.uv);
    
    float4 vVelocity = g_tex_1.Sample(g_sam_0, _in.uv);
    int iNumBlurSampling = 5;
    
    vVelocity.xy /= (float) iNumBlurSampling;
    vVelocity.x *= 7.f;
    int iCount = 1;
    
    for (int i = iCount; i < iNumBlurSampling; ++i)
    {
        float4 vBlurColor = g_tex_0.Sample(g_sam_0, _in.uv + vVelocity.xy * (float) i);
        vColor += vBlurColor;
        iCount++;
    }
    
    vColor /= iCount;
    
    if (iDistortionFlag)
    {
        float2 vDistortionUV = Distortion(_in.uv, fAccTime, fProgress);
        vColor = g_tex_0.Sample(g_sam_0, vDistortionUV);
    }
    
    if (iBrokenScreenFlag)
    {
        float2 vBrokenUV = BrokenScreen(_in.uv, float2(1.f, 1.f), fAccTime * 1.3f);
        vColor = g_tex_0.Sample(g_sam_0, vBrokenUV);
        vColor *= fProgress;
    }
    
    if (iAfterEffectFlag)
    {
        vColor = AfterColor(_in.uv, fAccTime);
    }
     
    float4 vLightColor = g_tex_2.Sample(g_sam_0, _in.uv) * fFadeRatio;
    float4 vTotalColor = vColor * vLightColor;
    
    if (iWhiteFadeFlag)
    {
        vTotalColor += float4(1.f, 1.f, 1.f, 1.f) * (1.f - fFadeRatio);
    }
    
    return vTotalColor;
}
#endif