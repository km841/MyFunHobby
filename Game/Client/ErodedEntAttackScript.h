#pragma once
#include "MonoBehaviour.h"
class ErodedEntAttackScript :
    public MonoBehaviour
{
public:
    ErodedEntAttackScript();
    virtual ~ErodedEntAttackScript();

public:
    virtual void LateUpdate() override;
};

