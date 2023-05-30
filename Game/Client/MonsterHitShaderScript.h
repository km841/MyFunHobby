#pragma once
#include "MonoBehaviour.h"
class MonsterHitShaderScript :
    public MonoBehaviour
{
public:
    MonsterHitShaderScript();
    virtual ~MonsterHitShaderScript();

public:
    virtual void LateUpdate() override;

private:
    float m_fRatio;
    MONSTER_STATE m_ePrevState;
};

