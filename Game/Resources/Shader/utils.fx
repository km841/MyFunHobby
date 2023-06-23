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

//#define NUM 30	// chip center point num
//#define DRAW_POINTS 0 // draw the center points
//#define DRAW_GAP_LINE 1 // draw the gap line

//float rnd(float2 s)
//{
//    return 1.0 - 2.0 * frac(sin(s.x * 253.13 + s.y * 341.41) * 589.19);
//}

//float rand(float x)
//{
//    return frac(sin(x * 873.15) * 519.19);
//}

//int GetNearPos(float2 p, float4 chipInfo[NUM])
//{
//    float2 v = chipInfo[0].xy;
//    int idx = 0;
//    for (int c = 0; c < NUM; c++)
//    {
//        float2 vc = chipInfo[c].xy;
//        float2 vp2 = vc - p;
//        float2 vp = v - p;
//        if (dot(vp2, vp2) < dot(vp, vp))
//        {
//            v = vc;
//            idx = c;
//        }
//    }
//    return idx;
//}

//float2 MoveOffset(int idx, float t, float4 chipInfo[NUM], float2 center)
//{
//    float2 offset = float2(0.0, 0.0);
//    float radVal = rand(float(idx + 1)) + 0.1;
//    float2 centerPos = chipInfo[idx].xy;
//    float2 diff = centerPos - center;
//    float dist = length(diff);
//    if (t > 0.0)
//    {
//        float2 initVel = normalize(diff) * dist * 1.0;
//        offset = initVel * t + float2(0.0, 1.0) * t * t * -0.5;
//    }
//    return offset;
//}

//float GetGapFactor(float2 p, float4 chipInfo[NUM], float2 center)
//{
//    float2 v = float2(1E3);
//    float2 v2 = float2(1E4);
//    for (int c = 0; c < NUM; c++)
//    {
//        float2 vc = chipInfo[c].xy;
//        if (length(vc - p) < length(v - p))
//        {
//            v2 = v;
//            v = vc;
//        }
//        else if (length(vc - p) < length(v2 - p))
//        {
//            v2 = vc;
//        }
//    }
//    float factor = abs(length(dot(p - v, normalize(v - v2))) - length(dot(p - v2, normalize(v - v2)))) + 0.002 * length(p - center);
//    factor = 7E-4 / factor;
//    if (length(v - v2) < 4E-3)
//        factor = 0.0;
//    if (factor < 0.01)
//        factor = 0.0;
//    return factor;
//}

//float4 mainImage(float2 fragCoord, float2 iResolution, sampler2D iChannel0, float iTime)
//{
//    float2 p = (fragCoord * 2.0 - iResolution.xy) / iResolution.x;

//    float2 center = float2(0.0, 0.0);
//    float isNear = 0.0;

//    float modT = fmod(iTime, 5.0);
//    float time = modT - 3.0;

//    float4 chipInfo[NUM];

//    for (int c = 0; c < NUM; c++)
//    {
//        float angle = floor(rnd(float2(float(c), 387.44)) * 16.0) * 3.1415 * 0.4 - 0.5;
//        float dist = pow(rnd(float2(float(c), 78.21)), 2.0) * 0.5;
//        float2 vc = float2(center.x + cos(angle) * dist, center.y + sin(angle) * dist);
//        chipInfo[c].xy = vc.xy;
//        chipInfo[c].zw = MoveOffset(c, time, chipInfo, center);
//    }

//    int belongIdx = -1;
//    for (int c = 0; c < NUM; c++)
//    {
//        float2 rawPos = p - chipInfo[c].zw;
//        int idx = GetNearPos(rawPos, chipInfo);
//        if (idx == c)
//        {
//            belongIdx = c;
//            break;
//        }
//    }

//    float3 finalCol = float3(0.0, 0.0, 0.0);

//    if (belongIdx != -1)
//    {
//        float2 moveOffset = chipInfo[belongIdx].zw;
//        float2 rawPos = p - moveOffset;
//        float2 rawCoord = (rawPos * iResolution.x + iResolution.xy) * 0.5;
//        rawCoord.y = iResolution.y - rawCoord.y;
//        float2 brokenOffset = float2(rnd(float2(belongIdx)) * 0.006);
//        float2 uv = (rawCoord.xy) / iResolution.xy + brokenOffset;

//        float4 tex = tex2D(iChannel0, uv);
//        finalCol = tex.xyz;

//        if (time > 0.0)
//        {
//            if (uv.x > 1.0 || uv.x < 0.0 || uv.y > 1.0 || uv.y < 0.0)
//            {
//                finalCol = float3(0.0, 0.0, 0.0);
//            }
//        }
//    }

//#if DRAW_GAP_LINE
//    if (time < 0.0)
//    {
//        float gapFactor = GetGapFactor(p, chipInfo, center);
//        finalCol = gapFactor * float3(1.0 - finalCol.xyz) + (1.0 - gapFactor) * finalCol.xyz;

//#if DRAW_POINTS
//        float isNear = 0.0;
//        for (int c = 0; c < NUM; c++)
//        {
//            float2 vc = chipInfo[c].xy;
//            if (length(vc - p) < 0.01)
//            {
//                isNear = 1.0;
//            }
//        }
//        finalCol = finalCol * (1.0 - isNear);
//#endif
//    }
//#endif

//    return float4(finalCol, 1.0);
//}
#endif