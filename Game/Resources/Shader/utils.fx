#ifndef _UTILS_FX_
#define _UTILS_FX_
#include "params.fx"

LightColor CalculateLightColor(int iLightIndex, float3 vViewPos)
{
    LightColor color = (LightColor) 0.f;
    
    float2 vViewLightDir = (float2) 0.f;
    
    float vDiffuseRatio = 1.f;
    float fDistanceRatio = 1.f;
    
    if (g_light[iLightIndex].lightType == 0)
    {
        vViewLightDir = normalize(mul(float4(g_light[iLightIndex].direction.xyz, 0.f), g_matView).xy);
    }
    else if (g_light[iLightIndex].lightType == 1)
    {
        float3 vViewLightPos = mul(float4(g_light[iLightIndex].position.xyz, 1.f), g_matView).xyz;
        vViewLightDir = normalize(vViewPos.xy - vViewLightPos.xy);
        
        float fDist = distance(vViewPos.xy, vViewLightPos.xy);
        if (g_light[iLightIndex].range == 0.f)
            vDiffuseRatio = 0.f;
        else 
            fDistanceRatio = 0.4f - fDist / g_light[iLightIndex].range;
    }
    else
    {
        // Spot Light
        float3 viewLightPos = mul(float4(g_light[iLightIndex].position.xyz, 1.f), g_matView).xyz;
        vViewLightDir = normalize(vViewPos.xy - viewLightPos.xy);

        if (g_light[iLightIndex].range == 0.f)
            fDistanceRatio = 0.f;
        else
        {
            float fHalfAngle = g_light[iLightIndex].angle / 2;

            float3 vViewLightVec = vViewPos - viewLightPos;
            float3 vViewCenterLightDir = normalize(mul(float4(g_light[iLightIndex].direction.xyz, 0.f), g_matView).xyz);

            float fCenterDist = dot(vViewLightVec, vViewCenterLightDir);
            fDistanceRatio = saturate(1.f - fCenterDist / g_light[iLightIndex].range);

            float fLightAngle = acos(dot(normalize(vViewLightVec), vViewCenterLightDir));

            if (fCenterDist < 0.f || fCenterDist > g_light[iLightIndex].range) // 최대 거리를 벗어났는지
                fDistanceRatio = 0.f;
            else if (fLightAngle > fHalfAngle) // 최대 시야각을 벗어났는지
                fDistanceRatio = 0.f;
            else // 거리에 따라 적절히 세기를 조절
                fDistanceRatio = saturate(1.f - pow(fCenterDist / g_light[iLightIndex].range, 2));
        }
    }
    
    color.diffuse = g_light[iLightIndex].color.diffuse * vDiffuseRatio * fDistanceRatio;
    color.ambient = g_light[iLightIndex].color.ambient * fDistanceRatio;

    return color;
}

float Rand(float2 co)
{
    return 0.5 + (frac(sin(dot(co.xy, float2(12.9898, 78.233))) * 43758.5453)) * 0.5;
}

float2 Distortion(float2 vUV, float fAccTime, float fProgress)
{
    // Align Center
    vUV -= 0.5f;
   
    float fRadius = length(vUV);
    float fTheta = atan2(vUV.y, vUV.x);
    
    float fPulse = sin(40 * fRadius - 10.0 * fAccTime) * fProgress;
    
    float2 fPulseRect = float2(fPulse * cos(fTheta), fPulse * sin(fTheta));
    
    vUV += 0.5f;
    return vUV + 0.02 * fPulseRect;
}

#define NUM 30	// chip center point num

float rnd(float2 s)
{
    return 1.0 - 2.0 * frac(sin(s.x * 253.13 + s.y * 341.41) * 589.19);
}

float rand(float x)
{
    return frac(sin(x * 873.15) * 519.19);
}

int GetNearPos(float2 p, float4 chipInfo[NUM])
{
    float2 v = chipInfo[0].xy;
    int idx = 0;
    for (int c = 0; c < NUM; c++)
    {
        float2 vc = chipInfo[c].xy;
        float2 vp2 = vc - p;
        float2 vp = v - p;
        if (dot(vp2, vp2) < dot(vp, vp))
        {
            v = vc;
            idx = c;
        }
    }
    return idx;
}

float2 MoveOffset(int idx, float t, float4 chipInfo[NUM], float2 center)
{
    float2 offset = float2(0.0, 0.0);
    float radVal = rand(float(idx + 1)) + 0.1;
    float2 centerPos = chipInfo[idx].xy;
    float2 diff = centerPos - center;
    float dist = length(diff);
    if (t > 0.0)
    {
        float2 initVel = normalize(diff) * dist * 1.0;
        offset = initVel * t + float2(0.0, 1.0) * t * t * -0.5;
    }
    return offset;
}

float2 BrokenScreen(float2 fragCoord, float2 iResolution, float iTime)
{
    float2 overturnY = float2(fragCoord.x, 1.f - fragCoord.y);
    float2 p = (overturnY * 2.0 - iResolution.xy) / iResolution.x;

    float2 center = float2(0.0, 0.0);
    float isNear = 0.0;

    float modT = fmod(iTime, 5.0);
    float time = modT - 3.0;

    float4 chipInfo[NUM];

    for (int c = 0; c < NUM; c++)
    {
        float angle = floor(rnd(float2(float(c), 387.44)) * 16.0) * 3.1415 * 0.4 - 0.5;
        float dist = pow(rnd(float2(float(c), 78.21)), 2.0) * 0.5;
        float2 vc = float2(center.x + cos(angle) * dist, center.y + sin(angle) * dist);
        chipInfo[c].xy = vc.xy;
        chipInfo[c].zw = MoveOffset(c, time, chipInfo, center);
    }

    int belongIdx = -1;
    for (int d = 0; d < NUM; d++)
    {
        float2 rawPos = p - chipInfo[d].zw;
        int idx = GetNearPos(rawPos, chipInfo);
        if (idx == d)
        {
            belongIdx = d;
            break;
        }
    }

    if (belongIdx != -1)
    {
        float2 moveOffset = chipInfo[belongIdx].zw;
        float2 rawPos = p - moveOffset;
        float2 rawCoord = (rawPos * iResolution.x + iResolution.xy) * 0.5;
        rawCoord.y = iResolution.y - rawCoord.y;
        float2 brokenOffset = float2(rnd(float(belongIdx)) * 0.006, 0.f);
        float2 uv = (rawCoord.xy) / iResolution.xy + brokenOffset;
        
        return uv;
    }
    
    return float2(0.f, 0.f);
}

#endif