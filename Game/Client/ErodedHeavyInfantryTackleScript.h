#pragma once
#include "MonoBehaviour.h"
class LocalEffect;
class ErodedHeavyInfantryTackleScript :
    public MonoBehaviour
{
public:
    ErodedHeavyInfantryTackleScript();
    virtual ~ErodedHeavyInfantryTackleScript();

public:
    virtual void LateUpdate() override;

private:
    void CreateFlashAuraAndAddedToScene();

private:
    weak_ptr<LocalEffect> m_pFlashAura;
    Timer m_tDamageTick;
};

