#pragma once
#include "BehaviorTask.h"
class VeteranHeroStingerEffectStateChangeTask :
    public BehaviorTask
{
public:
    VeteranHeroStingerEffectStateChangeTask(shared_ptr<GameObject> pGameObject, bool bState);
    virtual ~VeteranHeroStingerEffectStateChangeTask();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    bool m_bState;
};

