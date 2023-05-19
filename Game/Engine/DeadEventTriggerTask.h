#pragma once
#include "BehaviorTask.h"
class DeadEventTriggerTask :
    public BehaviorTask
{
public:
    DeadEventTriggerTask(shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;

private:
    bool m_bTrigger;
};

