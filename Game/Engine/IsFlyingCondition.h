#pragma once
#include "BehaviorCondition.h"
class IsFlyingCondition :
    public BehaviorCondition
{
public:
    IsFlyingCondition(shared_ptr<GameObject> pGameObject);
    virtual ~IsFlyingCondition();

public:
    virtual BEHAVIOR_RESULT Run() override;
};

