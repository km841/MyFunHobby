#pragma once
#include "BehaviorCondition.h"
class IsDeadCondition :
    public BehaviorCondition
{
public:
    IsDeadCondition(shared_ptr<GameObject> pGameObject);
    virtual ~IsDeadCondition();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
};

