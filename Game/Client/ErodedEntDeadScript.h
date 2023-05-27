#pragma once
#include "MonoBehaviour.h"
class ErodedEntDeadScript :
    public MonoBehaviour
{
public:
    ErodedEntDeadScript();
    virtual ~ErodedEntDeadScript();

public:
    virtual void LateUpdate() override;

private:
    void CreateExplosionEffectAndAddedToScene();

private:
    Timer m_tStayTimer;
};

