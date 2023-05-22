#pragma once
#include "MonoBehaviour.h"
class ErodedHeavyInfantryAttackScript :
    public MonoBehaviour
{
public:
    ErodedHeavyInfantryAttackScript();
    virtual ~ErodedHeavyInfantryAttackScript();

public:
    virtual void LateUpdate() override;

private:
    void CreateAttackSignAndAddedToScene();

private:
    bool m_bAttackFlag;
};

