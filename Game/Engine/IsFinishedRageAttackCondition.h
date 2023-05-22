#pragma once
#include "BehaviorCondition.h"
class IsFinishedRageAttackCondition :
    public BehaviorCondition
{
public:
    IsFinishedRageAttackCondition(shared_ptr<GameObject> pGameObject, int32 iAttackCount);
    virtual ~IsFinishedRageAttackCondition();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    int32 m_iAttackCount;
};

