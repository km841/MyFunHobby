#pragma once
#include "BehaviorTask.h"
class FlipDirectionTask :
    public BehaviorTask
{
public:
    FlipDirectionTask(shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;

private:
};

