#pragma once
#include "MonoBehaviour.h"
class ChimeraBreathFireEffectScript :
    public MonoBehaviour
{
public:
    ChimeraBreathFireEffectScript();
    virtual ~ChimeraBreathFireEffectScript();

public:
    virtual void LateUpdate() override;

private:
    void CreateBreathProjectileAndAddedToScene(const Vec3& vPos, const Vec3& vDir);

private:
    Timer m_tDuration;
    Timer m_tBreathTick;
    Vec3 m_vOrigin;
    float m_fBreathAcc;
    bool m_bOutroFlag;
};

