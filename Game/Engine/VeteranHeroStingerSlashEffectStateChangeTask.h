#pragma once
#include "BehaviorTask.h"
class VeteranHeroStingerSlashEffectStateChangeTask :
    public BehaviorTask
{
public:
    VeteranHeroStingerSlashEffectStateChangeTask(shared_ptr<GameObject> pGameObject);
    virtual ~VeteranHeroStingerSlashEffectStateChangeTask();

public:
    virtual BEHAVIOR_RESULT Run() override;
};

