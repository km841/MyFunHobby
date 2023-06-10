#pragma once
#include "BehaviorTask.h"
class AnimationClearTask :
    public BehaviorTask
{
public:
    AnimationClearTask(shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;
};

