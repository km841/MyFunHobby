#ifndef _PARTICLE_FX_
#define _PARTICLE_FX_

#include "params.fx"
#include "utils.fx"

struct Particle
{
    float4 vPosition;
    float4 vDirection;
    
    float fEndTime;
    float fCurTime;
    float fSpeed;
    uint  iAlive;
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

StructuredBuffer<Particle> particleBuffer : register(t9);

[maxvertexcount(6)]
void GS_Main(point VS_OUT input[1], inout TriangleStream<GS_OUT> triangleStream)
{
    GS_OUT output[4] = { (GS_OUT) 0.0f, (GS_OUT) 0.0f, (GS_OUT) 0.0f, (GS_OUT) 0.0f };
	
    if (0 == particleBuffer[input[0].id].iAlive)
        return;
	
    float3 vWorldPos = input[0].pos.xyz + particleBuffer[input[0].id].vPosition.xyz;
    float3 vViewPos = mul(float4(vWorldPos, 1.0f), g_matView).xyz;
    float3 vScale = float3(50.f, 50.f, 1.f);
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

RWStructuredBuffer<Particle> g_particle : register(u0);
RWStructuredBuffer<ParticleShared> g_shared : register(u1);

[numthreads(1024, 1, 1)]
void CS_Main(uint3 DTid : SV_DispatchThreadID)
{
    float4 vWorldPos = g_vec4_0;
    
    uint iMaxCount = g_int_0;
    
    float fRadius = g_float_0;
    float fStartSpeed = g_float_1;
    float fStartLifeTime = g_float_2;
    
    float fDeltaTime = g_vec2_0.x;
    float fElapsedTime = g_vec2_0.y;
    
    if (iMaxCount <= DTid.x)
        return;
    
    if (g_particle[DTid.x].iAlive == 0)
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
                g_particle[DTid.x].iAlive = 1;
                break;
            }
        }
        
        if (g_particle[DTid.x].iAlive)
        {
            float fSeedValue = ((float) DTid.x / (float) iMaxCount) + fElapsedTime;

            float fRand1 = Rand(float2(fSeedValue, fElapsedTime));
            float fRand2 = Rand(float2(fSeedValue * fElapsedTime * fElapsedTime, fElapsedTime * fElapsedTime));
            
            float2 fNoise =
            {
                2.f * fRand1 - 1.f,
                2.f * fRand2 - 1.f,
            };
            
            float2 fDir = (fNoise - 0.5f) * 2.f;
            g_particle[DTid.x].vDirection.xy = normalize(fDir);
            g_particle[DTid.x].vPosition.xyz = float3(400.f, 400.f, 80.f);
            
            g_particle[DTid.x].fCurTime = 0.f;
            g_particle[DTid.x].fSpeed = fStartSpeed;
            g_particle[DTid.x].fEndTime = fStartLifeTime;
            
        }
    }
    else
    {
        g_particle[DTid.x].fCurTime += fDeltaTime;
        if (g_particle[DTid.x].fEndTime < g_particle[DTid.x].fCurTime)
        {
            g_particle[DTid.x].iAlive = 0;
        }
        else
        {
            g_particle[DTid.x].vPosition += g_particle[DTid.x].vDirection * g_particle[DTid.x].fSpeed * fDeltaTime;
        }
    }
}

#endif