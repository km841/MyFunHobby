#pragma once
#include "MonoBehaviour.h"
class AbyssFieldDamageTickScript :
    public MonoBehaviour
{
public:
    AbyssFieldDamageTickScript();
    virtual ~AbyssFieldDamageTickScript();

public:
    virtual void LateUpdate() override;

private:
    Timer m_tDamageTick;
};

