#ifndef _DEBUG_GEOMETRY_FX_
#define _DEBUG_GEOMETRY_FX_

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
    float3 viewPos : POSITION;
};



VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    
    output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
    output.uv = _in.uv;
    
    output.viewPos = mul(float4(_in.pos, 1.f), g_matWV).xyz;
    return output;
}

Texture2D g_tex_0 : register(t0);
SamplerState g_sam_0 : register(s0);

struct PS_OUT
{
    float4 vPosition : SV_Target0;
    float4 vColor : SV_Target1;
};

PS_OUT PS_Main(VS_OUT _in) : SV_Target
{
    PS_OUT output = (PS_OUT) 0;
    
    output.vPosition = float4(_in.viewPos, 0.f);
    output.vColor = float4(0.f, 1.f, 0.f, 1.f);
    
    return output;
}
#endif