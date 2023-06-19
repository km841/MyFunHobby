#pragma once
#include "BehaviorTask.h"
class ChaseRandomSelectTask :
    public BehaviorTask
{
public:
    ChaseRandomSelectTask(shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;

private:
};

