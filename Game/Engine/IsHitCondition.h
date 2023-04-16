#pragma once
#include "BehaviorCondition.h"
class IsHitCondition :
    public BehaviorCondition
{
public:
    IsHitCondition(shared_ptr<GameObject> pGameObject);
    virtual ~IsHitCondition();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
};

