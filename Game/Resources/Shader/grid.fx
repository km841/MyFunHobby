#ifndef _GRID_FX_
#define _GRID_FX_

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
    float2 worldPos : POSITION;
};

// Grid Params
// g_float_0 : Thickness
// g_vec2_0  : Resolution
// g_vec2_1  : Grid Offset
// g_vec3_0  : Camera Position

VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    
    float2 resolution = g_vec2_0;
    float3 camera_position = g_vec3_0;

    output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
    output.uv = _in.uv;
    output.worldPos = _in.pos.xy * resolution.xy + camera_position.xy;
       
    return output;
}

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float thickness = g_float_0;
    float2 resolution = g_vec2_0;
    float2 grid_offset = g_vec2_1;
    
    const int width = grid_offset.x;
    const int height = (grid_offset.y * (resolution.y / resolution.x));

    if ((abs(_in.worldPos.x % width) <= thickness) || 
        (abs(_in.worldPos.y % height) <= thickness))
        return float4(1.0f, 1.0f, 1.0f, 1.0f);
    else
        discard;
    
    
    return float4(1.f, 0.f, 1.f, 1.f);
}
#endif