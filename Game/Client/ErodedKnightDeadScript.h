#pragma once
#include "MonoBehaviour.h"
class ErodedKnightDeadScript :
    public MonoBehaviour
{
public:
    ErodedKnightDeadScript();
    virtual ~ErodedKnightDeadScript();

public:
    virtual void LateUpdate() override;

private:
    void CreateExplosionEffectAndAddedToScene();

private:
    Timer m_tStayTimer;
};

