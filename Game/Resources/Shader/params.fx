#ifndef _PARAMS_FX_
#define _PARAMS_FX_

cbuffer TRANSFORM_PARAMS : register(b0)
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProjection;
    row_major matrix g_matWV;
    row_major matrix g_matWVP;
    row_major matrix g_matWVPInv;
}

cbuffer MATERIAL_PARAMS : register(b1)
{
    int g_int_0;
    int g_int_1;
    int g_int_2;
    int g_int_3;
    
    float g_float_0;
    float g_float_1;
    float g_float_2;
    float g_float_3;
    
    int g_tex_on_0;
    int g_tex_on_1;
    int g_tex_on_2;
    int g_tex_on_3;
    
    float2 g_vec2_0;
    float2 g_vec2_1;
    float2 g_vec2_2;
    float2 g_vec2_3;
    
    float3 g_vec3_0;
    float3 g_vec3_1;
    float3 g_vec3_2;
    float3 g_vec3_3;
    
    float4 g_vec4_0;
    float4 g_vec4_1;
    float4 g_vec4_2;
    float4 g_vec4_3;
}

struct LightColor
{
    float4 diffuse;
    float4 ambient;
    float4 specular;
};

struct LightInfo
{
    LightColor color;
    float4 position;
    float4 direction;
    int lightType;
    float range;
    float angle;
    int padding;
};

cbuffer LIGHT_PARAMS : register(b2)
{
    int g_lightCount;
    float3 g_lightPadding;
    LightInfo g_light[50];
}

cbuffer PARTICLE_PARAMS : register(b3)
{
    float4 g_worldPosition;
    float4 g_startColor;
    float4 g_startSize;
    
    uint g_maxParticles;
    uint g_simulationSpace;
    float g_radius;
    float g_startSpeed;
    
    float g_startLifeTime;
    float g_deltaTime;
    float g_elapsedTime; 
    int g_particlePadding;
}

#endif