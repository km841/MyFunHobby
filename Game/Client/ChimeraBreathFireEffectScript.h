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
    Timer m_tDuration;
    Vec3 m_vOrigin;
};

