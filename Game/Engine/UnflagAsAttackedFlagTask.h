#pragma once
#include "BehaviorTask.h"
class UnflagAsAttackedFlagTask :
    public BehaviorTask
{
public:
    UnflagAsAttackedFlagTask(shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;
};

