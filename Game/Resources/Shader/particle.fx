#ifndef _PARTICLE_FX_
#define _PARTICLE_FX_

#include "params.fx"
#include "utils.fx"

struct Particle
{
    float3 vPosition;
    float fEndTime;
    float3 vDirection;
    float fCurTime;
    
    float fSpeed;
    uint  iAlive;
    float2 vPadding;
};

struct ParticleShared
{
    uint iAdd;
};
struct VS_IN
{
    float4 pos : POSITION;
    uint id : SV_InstanceID;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    uint id : SV_InstanceID;
};

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.0f;
    
    output.pos = input.pos;
    output.id = input.id;
    
    return output;
}

struct GS_OUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
    uint id : SV_InstanceID;
};

// ========================
// Particle Geometry Shader
// ========================
// g_vec3_0 : Particle Scale

StructuredBuffer<Particle> particleBuffer : register(t9);

[maxvertexcount(6)]
void GS_Main(point VS_OUT input[1], inout TriangleStream<GS_OUT> triangleStream)
{
    GS_OUT output[4] = { (GS_OUT) 0.0f, (GS_OUT) 0.0f, (GS_OUT) 0.0f, (GS_OUT) 0.0f };
	
    if (0 == particleBuffer[input[0].id].iAlive)
        return;
	
    float3 vWorldPos = input[0].pos.xyz + particleBuffer[input[0].id].vPosition.xyz;
    float3 vViewPos = mul(float4(vWorldPos, 1.0f), g_matView).xyz;
    float3 vScale = g_vec3_0;
    
    float3 vNewPos[4] =
    {
        vViewPos + float3(-0.5f, 0.5f, 0.0f) * vScale,
        vViewPos + float3(0.5f, 0.5f, 0.0f) * vScale,
        vViewPos + float3(0.5f, -0.5f, 0.0f) * vScale,
        vViewPos + float3(-0.5f, -0.5f, 0.0f) * vScale
    };
	
    for (int i = 0; i < 4; i++)
    {
        output[i].pos = mul(float4(vNewPos[i], 1.0f), g_matProjection);
    }
	
    output[0].uv = float2(0.0f, 0.0f);
    output[1].uv = float2(1.0f, 0.0f);
    output[2].uv = float2(1.0f, 1.0f);
    output[3].uv = float2(0.0f, 1.0f);
	
    output[0].id = input[0].id;
    output[1].id = input[0].id;
    output[2].id = input[0].id;
    output[3].id = input[0].id;
    
    triangleStream.Append(output[0]);
    triangleStream.Append(output[1]);
    triangleStream.Append(output[2]);
    triangleStream.RestartStrip();
    
    triangleStream.Append(output[0]);
    triangleStream.Append(output[2]);
    triangleStream.Append(output[3]);
    triangleStream.RestartStrip();
}

Texture2D g_tex_0 : register(t0);
SamplerState g_sam_0 : register(s0);

float4 PS_Main(GS_OUT input) : SV_TARGET
{
    float4 output = (float4) 0.0f;
    output = g_tex_0.Sample(g_sam_0, input.uv);
    
    return output;
}

// =======================
// Particle Compute Shader
// =======================
// g_vec3_0  : World Position
// g_int_0   : Particle Max Count
// g_float_0 : Particle Creation Radius
// g_float_1 : Particle Start Speed
// g_float_2 : Particle Life Time (Maximum)
// g_vec2_0  : Delta Time / Elapsed Time

RWStructuredBuffer<Particle> g_particle : register(u0);
RWStructuredBuffer<ParticleShared> g_shared : register(u1);

[numthreads(1024, 1, 1)]
void CS_Main(uint3 threadIndex : SV_DispatchThreadID)
{
    float3 vWorldPos = g_vec3_0;
    
    uint iMaxCount = g_int_0;
    
    float fRadius = g_float_0;
    float fStartSpeed = g_float_1;
    float fStartLifeTime = g_float_2;
    
    float fDeltaTime = g_vec2_0.x;
    float fElapsedTime = g_vec2_0.y;
    
    if (iMaxCount <= threadIndex.x)
        return;
    
    if (0 == g_particle[threadIndex.x].iAlive)
    {
        while (true)
        {
            int iRemaining = g_shared[0].iAdd;
            if (iRemaining <= 0)
                break;

            int iExpected = iRemaining;
            int iDesired = iRemaining - 1;
            int iOriginalValue;
            InterlockedCompareExchange(g_shared[0].iAdd, iExpected, iDesired, iOriginalValue);

            if (iOriginalValue == iExpected)
            {
                g_particle[threadIndex.x].iAlive = 1;
                break;
            }
        }
        
        if (1 == g_particle[threadIndex.x].iAlive)
        {
            float fSeedValue = ((float) threadIndex.x / (float) iMaxCount) + fElapsedTime;

            float fRand1 = Rand(float2(fSeedValue, fElapsedTime));
            float fRand2 = Rand(float2(fSeedValue * fElapsedTime * fElapsedTime, fElapsedTime * fElapsedTime));
            
            float2 fNoise =
            {
                2.f * fRand1 - 1.f,
                2.f * fRand2 - 1.f,
            };
            
            float2 fDir = (fNoise - 0.5f) * 2.f;
            g_particle[threadIndex.x].vDirection.xy = normalize(fDir);
            g_particle[threadIndex.x].vPosition.xyz = vWorldPos;
            
            g_particle[threadIndex.x].fCurTime = 0.f;
            g_particle[threadIndex.x].fSpeed = fStartSpeed;
            g_particle[threadIndex.x].fEndTime = fStartLifeTime;
            
        }
    }
    else
    {
        g_particle[threadIndex.x].fCurTime += fDeltaTime;
        if (g_particle[threadIndex.x].fEndTime < g_particle[threadIndex.x].fCurTime)
        {
            g_particle[threadIndex.x].iAlive = 0;
        }
        else
        {
            g_particle[threadIndex.x].vPosition += g_particle[threadIndex.x].vDirection * g_particle[threadIndex.x].fSpeed * fDeltaTime;
        }
    }
}

#endif