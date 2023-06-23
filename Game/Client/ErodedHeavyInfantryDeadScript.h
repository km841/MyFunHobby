#pragma once
#include "MonoBehaviour.h"
class ErodedHeavyInfantryDeadScript :
    public MonoBehaviour
{
public:
    ErodedHeavyInfantryDeadScript();
    virtual ~ErodedHeavyInfantryDeadScript();

public:
    virtual void LateUpdate() override;

private:
    void CreateExplosionEffectAndAddedToScene();

private:
    Timer m_tStayTimer;
    bool m_bDeadBeginFlag;
};

