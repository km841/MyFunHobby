#pragma once
#include "BehaviorTask.h"
class VeteranHeroRandomStateTask :
    public BehaviorTask
{
public:
    VeteranHeroRandomStateTask(shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;

private:
};

