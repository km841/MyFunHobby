#pragma once
#include "BehaviorCondition.h"
class IsGroundCondition :
    public BehaviorCondition
{
public:
    IsGroundCondition(shared_ptr<GameObject> pGameObject);
    virtual ~IsGroundCondition();

public:
    virtual BEHAVIOR_RESULT Run() override;
};

