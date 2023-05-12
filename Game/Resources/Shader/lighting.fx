#ifndef _LIGHTING_FX_
#define _LIGHTING_FX_

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
SamplerState g_sam_0 : register(s0);

VS_OUT VS_DirLight(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    output.pos = float4(_in.pos, 1.f);
    output.uv = _in.uv;
    
    return output;
}


// Lighting Params
// g_int_0 : Light Index
// g_tex_0 : Position RenderTarget

struct PS_OUT
{
    float4 vDiffuse : SV_Target0;
};

PS_OUT PS_DirLight(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0;
    
    float3 vViewPos = g_tex_0.Sample(g_sam_0, _in.uv).xyz;
    if (vViewPos.z <= 0.f)
        clip(-1);
    
    LightColor color = CalculateLightColor(g_int_0, vViewPos);
    output.vDiffuse += color.diffuse + color.ambient;
        
    return output;
}

// Point Params
// g_int_0 : Light Index
// g_vec2_0 : RenderTarget Resolution
// g_tex_0 : Position RenderTarget
// g_tex_1 : Diffuse Light RenderTarget

VS_OUT VS_PointLight(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
    output.uv = _in.uv;
    
    return output;
}

PS_OUT PS_PointLight(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0;
    
    float2 vUV = float2(_in.pos.x / g_vec2_0.x, _in.pos.y / g_vec2_0.y);
    float3 vViewPos = g_tex_0.Sample(g_sam_0, vUV).xyz;
    if (vViewPos.z <= 0.f)
        clip(-1);
    
    int iLightIndex = g_int_0;
    float4 vViewLightPos = mul(float4(g_light[iLightIndex].position.xyz, 1.f), g_matView);
    float fDistance = length(vViewPos.xy - vViewLightPos.xy);
    if (fDistance > g_light[iLightIndex].range)
        clip(-1);
    
    LightColor color = CalculateLightColor(iLightIndex, vViewPos);
   
    output.vDiffuse = color.diffuse + color.ambient;
    return output;
}
#endif