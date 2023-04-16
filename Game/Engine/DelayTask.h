#pragma once
#include "BehaviorTask.h"
class DelayTask :
    public BehaviorTask
{
public:
    DelayTask(shared_ptr<GameObject> pGameObject, float fDuration);
    virtual BEHAVIOR_RESULT Run() override;

private:
    Timer m_tDuration;
    bool m_bHitFlag;
};

