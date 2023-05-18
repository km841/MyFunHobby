#pragma once
#include "BehaviorCondition.h"
class TimerCondition :
    public BehaviorCondition
{
public:
    TimerCondition(shared_ptr<GameObject> pGameObject, float fDuration);
    virtual BEHAVIOR_RESULT Run() override;

private:
    Timer m_tDuration;
};

