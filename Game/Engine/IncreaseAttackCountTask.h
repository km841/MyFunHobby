#pragma once
#include "BehaviorTask.h"
class IncreaseAttackCountTask :
    public BehaviorTask
{
public:
    IncreaseAttackCountTask(shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;
};

