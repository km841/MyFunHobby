#pragma once
#include "BehaviorTask.h"
class RemoveObjectTask :
    public BehaviorTask
{
public:
    RemoveObjectTask(shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;

private:
};

