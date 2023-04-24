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
    
    output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
    output.normal = normalize(mul(float4(_in.normal, 0.f), g_matWV)).xyz;
    output.uv = _in.uv;
    
    float4 vNewProjPos = output.pos;
    float4 vOldViewPos = mul(float4(_in.pos, 1.f), g_matOldWV);
    float4 vOldProjPos = mul(float4(vOldViewPos.xyz, 1.f), g_matProjection);
    
    float3 vDir = vNewProjPos.xyz - vOldProjPos.xyz;
    
    float fCheck = dot(normalize(vDir), normalize(output.normal));
    
    if (fCheck < 0.f)
        output.pos = vNewProjPos;
    else
        output.pos = vOldProjPos;
    
    
    float2 vVelocity = vNewProjPos.xy - vOldProjPos.xy;
    output.dir.xy = vVelocity * 0.5f;
    output.dir.y *= -1.f;
    output.dir.z = output.pos.z;
    //output.dir.w = 1.f;
    
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
    
    float4 vColor = g_tex_0.Sample(g_sam_0, _in.uv);
    //if (vColor.a <= 0.1f)
    //    discard;
        
    output.vVelocity.xy = _in.dir.xy;
    output.vVelocity.z = 1.f;
    
    //output.vVelocity = float4(1.f, 0.f, 0.f, 1.f);
    
    return output;
}
#endif