#ifndef _UTILS_FX_
#define _UTILS_FX_
#include "params.fx"

LightColor CalculateLightColor(int iLightIndex, float3 vViewPos)
{
    LightColor color = (LightColor) 0.f;
    
    float3 vViewLightDir = (float3) 0.f;
    
    float vDiffuseRatio = 1.f;
    float fDistanceRatio = 1.f;
    
    if (g_light[iLightIndex].lightType == 0)
    {
        vViewLightDir = normalize(mul(float4(g_light[iLightIndex].direction.xyz, 0.f), g_matView).xyz);
    }
    else if (g_light[iLightIndex].lightType == 1)
    {
        float3 vViewLightPos = mul(float4(g_light[iLightIndex].position.xyz, 1.f), g_matView).xyz;
        vViewLightDir = normalize(vViewPos - vViewLightPos);
        
        float fDist = distance(vViewPos, vViewLightPos);
        if (g_light[iLightIndex].range == 0.f)
            vDiffuseRatio = 0.f;
        else 
            fDistanceRatio = 1.f - pow(fDist / g_light[iLightIndex].range, 2);
    }
    else
    {
        // Spot Light
        float3 viewLightPos = mul(float4(g_light[iLightIndex].position.xyz, 1.f), g_matView).xyz;
        vViewLightDir = normalize(vViewPos - viewLightPos);

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

#endif