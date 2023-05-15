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
    float2 fGravityAcc;
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

// ==========================
//  Particle Geometry Shader
// ==========================
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
    float fElapsedTime = g_vec2_0.y;
    float4 output = (float4) 0.0f;
    output = g_tex_0.Sample(g_sam_0, input.uv);
    
    float fCurTime = particleBuffer[input.id].fCurTime;
    float fEndTime = particleBuffer[input.id].fEndTime;
    
    output.a = 1.f - fCurTime / fEndTime;
    
    return output;
}

// =========================
//  Particle Compute Shader
// =========================
// g_vec3_0  : World Position
// g_int_0   : Particle Max Count
// g_float_0 : Particle Life Time (Maximum)
// g_float_1 : Gravity
// g_vec2_0  : Delta Time / Elapsed Time
// g_vec2_1  : Particle Start Speed (Range) / Particle End Speed (Range)
// g_vec2_2  : Particle Start Angle (Range) / Particle End Angle (Range)

RWStructuredBuffer<Particle> g_particle : register(u0);
RWStructuredBuffer<ParticleShared> g_shared : register(u1);

[numthreads(1024, 1, 1)]
void CS_Main(uint3 threadIndex : SV_DispatchThreadID)
{
    float3 vWorldPos = g_vec3_0;
    
    uint iMaxCount = g_int_0;

    float fStartLifeTime = g_float_0;
    float fGravity = g_float_1;
    
    float fDeltaTime = g_vec2_0.x;
    float fElapsedTime = g_vec2_0.y;
    
    int iStartSpeed = (int) g_vec2_1.x;
    int iEndSpeed = (int) g_vec2_1.y;
    
    int iStartAngle = (int) g_vec2_2.x;
    int iEndAngle = (int) g_vec2_2.y;
    
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
            float fRand2 = Rand(float2(fSeedValue * fElapsedTime, fElapsedTime));
            
            float2 fNoise =
            {
                2.f * fRand1 - 1.f,
                2.f * fRand2 - 1.f,
            };
            
            float fRandSpeed = lerp((float) iStartSpeed, (float) iEndSpeed, fNoise.x);
            float fRandAngle = lerp((float) iStartAngle, (float) iEndAngle, fNoise.y);
            float fRandRadian = fRandAngle * 3.141592f / 180.f;
            
            float2 vRightNormal = float2(1.f, 0.f);
            float fRotatedX = vRightNormal.x * cos(fRandRadian) + vRightNormal.y * sin(fRandRadian);
            float fRotatedY = vRightNormal.x * sin(fRandRadian) - vRightNormal.y * cos(fRandRadian);

            g_particle[threadIndex.x].vDirection.xy = float2(fRotatedX, fRotatedY);
            g_particle[threadIndex.x].vPosition.xyz = vWorldPos;
            
            g_particle[threadIndex.x].fGravityAcc = 0.f;
            g_particle[threadIndex.x].fCurTime = 0.f;
            g_particle[threadIndex.x].fSpeed = fRandSpeed;
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
            g_particle[threadIndex.x].fGravityAcc.y += fGravity * fDeltaTime;
            g_particle[threadIndex.x].vPosition += g_particle[threadIndex.x].vDirection * g_particle[threadIndex.x].fSpeed * fDeltaTime;
            g_particle[threadIndex.x].vPosition.y += g_particle[threadIndex.x].fGravityAcc.y * fDeltaTime;
        }
    }
}

#endif