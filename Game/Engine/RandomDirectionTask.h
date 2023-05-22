#pragma once
#include "BehaviorTask.h"
class RandomDirectionTask :
    public BehaviorTask
{
public:
    RandomDirectionTask(shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;
};

